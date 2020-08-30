// Fill out your copyright notice in the Description page of Project Settings.


#include "BossWeaponCollider.h"
#include "Classes/Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "cppSlasherCharacter.h"


// Sets default values
ABossWeaponCollider::ABossWeaponCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABossWeaponCollider::setCollisionOn(bool isOn)
{
	canHitEnemies = isOn;
}

// Called when the game starts or when spawned
void ABossWeaponCollider::BeginPlay()
{
	Super::BeginPlay();
	//initialize root component
	weaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("weaponRoot"));
	RootComponent = weaponRoot;


	//initialize the box collider for the weapon
	weaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("weaponCollider"));
	weaponCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//setting up the collider to be able to generate overlap events
	weaponCollider->SetGenerateOverlapEvents(true);
	weaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ABossWeaponCollider::onSwordHit);
	weaponCollider->AttachToComponent(weaponRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ABossWeaponCollider::onSwordHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

// Called every frame
void ABossWeaponCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

