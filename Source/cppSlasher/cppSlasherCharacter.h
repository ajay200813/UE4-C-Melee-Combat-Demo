// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "baseSword.h"
#include "cppSlasherCharacter.generated.h"

UCLASS(config=Game)
class AcppSlasherCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//anim montage for the sword attacks
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* SwordAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* rollMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* blockMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* damageMontage;
public:
	AcppSlasherCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = baseStats)
		float maxHealth = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = baseStats)
		float maxStamina = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = baseStats)
		float currentHealth = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = baseStats)
		float currentStamina = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=MovementStats)
	float PlayerBaseSpeed = 400.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = MovementStats)
	float PlayerSprintSpeed = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		float playerArmour = 0.f;
	//variables dictating the player's attacks 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
	bool canAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		bool canRoll = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		bool canBlock = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		bool isHoldingBlock = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackVariables)
	int comboCounter = 1; //used to store the current number of attacks that have been performed in a combo - will always be reset back to 1
	//create variable for the weapon
	UPROPERTY(EditAnywhere)
	TSubclassOf<AbaseSword> playerWeapon;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AbaseSword> playerWeaponLeftHand;


	AbaseSword* equippedSword;
	AbaseSword* equippedSwordLeftHand;

	UPlayerInput* playerInput;
	//functions handling the logic for the attack
	void StartAttack();
	void StartBlock();
	void EndBlock();
	void EndAttack();
	UFUNCTION(BlueprintCallable)
	void takeDamage(float damage);
	//used to tell actor whether it should be adding to rotation during the roll
	bool shouldRotate = false;
	void startRotatingWithLimit(); //begins rotating the player upon rolling
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackVariables)
	bool isInIFrame = false; //used to determine whether enemy attacks can hit the character during a rolling animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackVariables)
	bool isInParryFrame = false;

	void StopSprinting(); //stop sprinting is public so it can be called when taking damage or rolling
protected:

	virtual void BeginPlay() override;
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//two functions that handle changing the player move speed while shift is held
	void StartSprinting();
	

	void StartRolling();
	//used to trigger the animation for each attack
	void AttackInput();

	FRotator GetRollDirection();

	float rollTimeElapsed = 0; //the amount of time that has elapsed since actor started its current roll
	float rotateTime = 0;
	//variables dictating roll direction change
	float maxPosRotation = 180.f;
	float maxDegreesPerSec = 720.f;

	FKey sprintKeyKeyBoard; //to get references to the sprint keys so the game can detect if the sprint key is held down after sprint is interrupted
	FKey sprintKeyGamePad;
	bool isSprinting = false;
	//can be called by blueprints for testing purposes
	UFUNCTION(BlueprintCallable)
	void SpawnWeapon();

	virtual void Tick(float DeltaTime) override;
	

	void ResetCanBlock(); //used to stop the player from spamming block inputs and making the character flail about
	FTimerHandle blockTimerHandle; //timer handle for the timer function used to call the ResetCanBlock function
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

