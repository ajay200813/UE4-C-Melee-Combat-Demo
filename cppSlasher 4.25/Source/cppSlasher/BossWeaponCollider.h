// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossWeaponCollider.generated.h"

UCLASS()
class CPPSLASHER_API ABossWeaponCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossWeaponCollider();

	UPROPERTY(EditAnywhere)
		USceneComponent* weaponRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TheCollider)
		class UBoxComponent* weaponCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float weaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float armourPenetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		bool canHitEnemies = false;

	UFUNCTION()
		void setCollisionOn(bool isOn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void onSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
