// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "cppSlasherCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
//#include "Engine.h"
//////////////////////////////////////////////////////////////////////////
// AcppSlasherCharacter

#define COMBO_MAX 5
#define BLOCK_RESET_TIMER 1.f
AcppSlasherCharacter::AcppSlasherCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->MaxWalkSpeed = PlayerBaseSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//create constructor helpers to load the attack animation montage
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordAttackMontageObject(TEXT("AnimMontage'/Game/Mannequin/Animations/playerAttackMontage.playerAttackMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordAttackMontageObject(TEXT("AnimMontage'/Game/ParagonCountess/Characters/Heroes/Countess/Animations/animsToSteal/twin_sword_montage.twin_sword_montage'"));
	if (SwordAttackMontageObject.Succeeded())
	{
		SwordAttackMontage = SwordAttackMontageObject.Object;
	}
	//create constructor helpers again to load the rolling animation montage
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageObject(TEXT("AnimMontage'/Game/Mannequin/Animations/playerRollMontage.playerRollMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageObject(TEXT("AnimMontage'/Game/ParagonCountess/Characters/Heroes/Countess/Animations/animsToSteal/roll_montage.roll_montage'"));
	if (RollMontageObject.Succeeded())
	{
		rollMontage = RollMontageObject.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BlockMontageObject(TEXT("AnimMontage'/Game/ParagonCountess/Characters/Heroes/Countess/Animations/animsToSteal/block_montage.block_montage'"));
	if (BlockMontageObject.Succeeded())
	{
		blockMontage = BlockMontageObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DamageMontageObject(TEXT("AnimMontage'/Game/ParagonCountess/Characters/Heroes/Countess/Animations/animsToSteal/hit_montage.hit_montage'"));
	if (DamageMontageObject.Succeeded())
	{
		damageMontage = DamageMontageObject.Object;
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AcppSlasherCharacter::AttackInput()
{
	if (canAttack && (!GetCharacterMovement()->IsFalling()) && currentStamina >= 5.f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, FString::FromInt(comboCounter));
		FString attackName = FString("start_") + FString::FromInt(comboCounter);
		PlayAnimMontage(SwordAttackMontage, 1.f, FName(*attackName));
		comboCounter++;
		canAttack = false;
		canRoll = false;
		canBlock = false;
		currentStamina -= 5.f;
	}
}



void AcppSlasherCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	APlayerCameraManager* const cam_manager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	cam_manager->ViewPitchMin = -40.f;
	cam_manager->ViewPitchMax = 60.f;
	currentHealth = maxHealth;
	currentStamina = maxStamina;
	
	playerInput = GetWorld()->GetFirstPlayerController()->PlayerInput;
	TArray<FInputActionKeyMapping> q = playerInput->GetKeysForAction(FName("Sprint"));
	sprintKeyKeyBoard = q[0].Key;
	//FKey B = q[1].Key;
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta,sprintKeyKeyBoard.GetFName().ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, B.GetFName().ToString());
}

void AcppSlasherCharacter::OnResetVR()
{
}





void AcppSlasherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); //can uncomment these if I want character to jump, but for now i dont want it
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AcppSlasherCharacter::StartRolling);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AcppSlasherCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AcppSlasherCharacter::StopSprinting);

	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &AcppSlasherCharacter::AttackInput);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AcppSlasherCharacter::StartBlock);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AcppSlasherCharacter::EndBlock);
	//PlayerInputComponent->BindAction("LightAttack", IE_Released, this, &AcppSlasherCharacter::EndAttack);
	PlayerInputComponent->BindAxis("MoveForward", this, &AcppSlasherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AcppSlasherCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AcppSlasherCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AcppSlasherCharacter::LookUpAtRate);

	
}



void AcppSlasherCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (isSprinting && GetCharacterMovement()->Velocity != FVector(0,0,0))
	{
		currentStamina -= 10 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	}
	else if (!isSprinting && canAttack && currentStamina < maxStamina)
	{
		currentStamina += 5 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	}
	
	
	
	if (UGameplayStatics::GetPlayerController(this,0)->GetInputKeyTimeDown(sprintKeyKeyBoard) > 2.0f && canRoll)
	{
		StartSprinting();
	}
	if (shouldRotate)
	{
		rollTimeElapsed = (rollTimeElapsed + UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
		if (rollTimeElapsed <= rotateTime)
		{
			SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), GetRollDirection(), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), maxDegreesPerSec));
		}
	}

}
void AcppSlasherCharacter::ResetCanBlock()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	canBlock = true;
}
void AcppSlasherCharacter::SpawnWeapon()
{
	if (playerWeapon && playerWeaponLeftHand)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			//FActorSpawnParameters spawnParams;
			//spawnParams.Owner = this;
			FRotator rotator = GetActorRotation();

			FVector spawnLocation = GetActorLocation();
			equippedSword = world->SpawnActor<AbaseSword>(playerWeapon, spawnLocation, rotator);
			equippedSword->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("custom_weapon_socket_r"));

			equippedSwordLeftHand = world->SpawnActor<AbaseSword>(playerWeaponLeftHand, spawnLocation, rotator);
			equippedSwordLeftHand->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("custom_weapon_socket_l"));


		}
	}
}

void AcppSlasherCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AcppSlasherCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AcppSlasherCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AcppSlasherCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AcppSlasherCharacter::StartSprinting()
{
	isSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = PlayerSprintSpeed;
}
void AcppSlasherCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerBaseSpeed;
	isSprinting = false;
}

void AcppSlasherCharacter::StartRolling()
{
	if (canRoll && !GetCharacterMovement()->IsFalling() && currentStamina >= 10) //want to be able to break out of attacks to roll at the same time as you would be able to start comboing
	{
		//if (GetCharacterMovement()->GetLastInputVector() != FVector(0, 0, 0))
		if(GetLastMovementInputVector() != FVector(0,0,0)) //checks to see if the player has input a movement command - if they have, they will roll. if they haven't, the character will perform a backstep
		{
			//SetActorRotation(GetRollDirection()); //gets a rotation based off of the direction of the most recent player input and rotates the player to face that way before rolling
			
			PlayAnimMontage(rollMontage, 1.f, FName("roll"));
		}
		else
		{	
			PlayAnimMontage(rollMontage, 1.f, FName("stepback"));
		}
		currentStamina -= 10;
	}
}

void AcppSlasherCharacter::StartAttack()
{
	
	if ((comboCounter - 1) % 2 == 0) //checks to see if the combo number (which is already increased by 1, hence the -1) is odd or even and turns on the collision for the appropriate sword.
	{
		equippedSwordLeftHand->setCollisionOn(true);
		
	}
	else if (comboCounter - 1 == COMBO_MAX) //if the attack is the last hit of the combo both swords are turned on, as it is a double slash that needs to deal more damage
	{
		equippedSwordLeftHand->setCollisionOn(true);
		equippedSword->setCollisionOn(true);
			
	}
	else
	{
		equippedSword->setCollisionOn(true);
			
	}
		
	
	
	
	
}

void AcppSlasherCharacter::StartBlock()
{
	if (canBlock)
	{
		PlayAnimMontage(blockMontage, 1.f, FName("Default"));
		isHoldingBlock = true;
		canAttack = false;
		canRoll = false;
		canBlock = false;
		GetCharacterMovement()->Deactivate();
	}
	
}
void AcppSlasherCharacter::EndBlock()
{
	if (isHoldingBlock)
	{
		isHoldingBlock = false;
		canAttack = true;
		comboCounter = 1; //player could store combos using the block due to combo reset relying on canattack to be true
		canRoll = true;
		//canBlock = true;
		GetCharacterMovement()->Activate();
		GetWorldTimerManager().SetTimer(blockTimerHandle, this, &AcppSlasherCharacter::ResetCanBlock, BLOCK_RESET_TIMER, false);
	}

}
void AcppSlasherCharacter::EndAttack()
{
	equippedSword->setCollisionOn(false);
	equippedSwordLeftHand->setCollisionOn(false);
	equippedSword->resetAttackHitArray();
	equippedSwordLeftHand->resetAttackHitArray();
}

void AcppSlasherCharacter::takeDamage(float damage)
{
	currentHealth -= damage;
	PlayAnimMontage(damageMontage, 1.0f);
	if (currentHealth <= 0)
	{
		canAttack = false;
		canRoll = false;
		canBlock = false;
		GetCharacterMovement()->SetActive(false);
	}

}

FRotator AcppSlasherCharacter::GetRollDirection()
{
	if (GetLastMovementInputVector() != FVector(0, 0, 0))
	{
		return UKismetMathLibrary::MakeRotFromX(GetLastMovementInputVector());
	}
	else
	{
		return GetActorRotation();
	}
	//return FRotator();
}

void AcppSlasherCharacter::startRotatingWithLimit()
{
	rotateTime = maxPosRotation / maxDegreesPerSec;
	rollTimeElapsed = 0.f;
	shouldRotate = true;
}
