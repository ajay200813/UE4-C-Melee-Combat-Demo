// Fill out your copyright notice in the Description page of Project Settings.


#include "enemyNPC.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AenemyNPC::AenemyNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AenemyNPC::BeginPlay()
{
	Super::BeginPlay();
	playerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

// Called every frame
void AenemyNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AenemyNPC::takeDamage(float damageValue, float armourPen)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, "Oh boy, this is still the default class");
	float newArmour = (armour - armourPen); //armour and armourPen should both be floats between 0 and 1, acting as percentages where 1.0 armour blocks all damage
	newArmour = FMath::Clamp(newArmour, 0.0f, 1.0f); //ensures armour cannot drop below 0 to make the player do more damage than intended
	currentHealth -= damageValue * (1 - newArmour);
	toNextStagger -= damageValue;
	//FString floatString = FString::SanitizeFloat(currentHealth);
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, *floatString);
	//currentHealth -= damageValue;
}

void AenemyNPC::TurnToFacePlayer()
{
	FRotator r = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerChar->GetActorLocation());
	r.Pitch = 0;
	SetActorRotation(r);
}

void AenemyNPC::MeleeAttack()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}

}

void AenemyNPC::JumpAttack()
{
	if (jumpMontage)
	{
		PlayAnimMontage(jumpMontage);
	}
}

UAnimMontage * AenemyNPC::GetMontage() const
{
	return montage;
}

UAnimMontage * AenemyNPC::GetJumpMontage() const
{
	return jumpMontage;
}