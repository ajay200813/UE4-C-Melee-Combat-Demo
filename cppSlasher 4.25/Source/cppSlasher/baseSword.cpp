// Fill out your copyright notice in the Description page of Project Settings.

#include "baseSword.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Classes/Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "enemyNPC.h"
#include "baseSword.h"

//#include "Engine.h"
// Sets default values
AbaseSword::AbaseSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialize root component
	swordRoot = CreateDefaultSubobject<USceneComponent>(TEXT("swordRoot"));
	RootComponent = swordRoot;
	
	//initialize the mesh component and attach it to the root object
	swordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("swordMesh"));
	swordMesh->AttachToComponent(swordRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//initialize the box collider for the weapon
	swordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("swordCollider"));
	swordCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//setting up the collider to be able to generate overlap events
	swordCollider->SetGenerateOverlapEvents(true);
	swordCollider->OnComponentBeginOverlap.AddDynamic(this, &AbaseSword::onSwordHit);
	swordCollider->AttachToComponent(swordRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	hitThisAttack.SetNum(4);
	//swordCollider->SetCollisionProfileName("NoCollision");
	
}

void AbaseSword::setCollisionOn(bool isOn)
{
	canHitEnemies = isOn;

}


// Called when the game starts or when spawned
void AbaseSword::BeginPlay()
{
	Super::BeginPlay();
	
}

void AbaseSword::onSwordHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != NULL && canHitEnemies)
	{
		if (OtherActor->IsA(AenemyNPC::StaticClass()) && !hitThisAttack.Contains(OtherActor)) //checks if OtherActor inherits from a certain type - will place the custom base enemy type here once created
		{
			//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, OtherActor->GetName());
			AenemyNPC* thisEnemy = Cast<AenemyNPC>(OtherActor);
			thisEnemy->takeDamage(weaponDamage,armourPenetration);
			hitThisAttack.Add(OtherActor);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, OtherActor->GetName());
}

// Called every frame
void AbaseSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AbaseSword::resetAttackHitArray()
{
	//clears the array at the end of each attack so that any followup attacks can still hit the enemy
	hitThisAttack.Empty();
}




