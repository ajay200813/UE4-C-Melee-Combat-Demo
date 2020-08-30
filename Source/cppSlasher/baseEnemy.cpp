// Fill out your copyright notice in the Description page of Project Settings.


#include "baseEnemy.h"
#include "Math/UnrealMathUtility.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
// Sets default values
AbaseEnemy::AbaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//initialize root component
	enemyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("enemyRoot"));
	RootComponent = enemyRoot;

	//initialize the mesh component and attach it to the root object
	enemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("enemyMesh"));
	enemyMesh->AttachToComponent(enemyRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


}

// Called when the game starts or when spawned
void AbaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AbaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AbaseEnemy::takeDamage(float damageValue,float armourPen)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, "Oh boy, this is still the default class");
	float newArmour = (armour - armourPen); //armour and armourPen should both be floats between 0 and 1, acting as percentages where 1.0 armour blocks all damage
	newArmour = FMath::Clamp(newArmour, 0.0f, 1.0f); //ensures armour cannot drop below 0 to make the player do more damage than intended
	currentHealth -= damageValue * (1 - newArmour); 
	FString floatString = FString::SanitizeFloat(currentHealth);
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta,*floatString);
	//currentHealth -= damageValue;
}



