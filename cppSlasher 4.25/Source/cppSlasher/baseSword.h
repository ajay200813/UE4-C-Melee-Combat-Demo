// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "baseSword.generated.h"


UCLASS(Blueprintable)
class CPPSLASHER_API AbaseSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AbaseSword();

	UPROPERTY(EditAnywhere)
		USceneComponent* swordRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* swordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* swordCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float weaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float armourPenetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackVariables)
		bool canHitEnemies = false;

	UFUNCTION()
		void setCollisionOn(bool isOn);

	UFUNCTION()
		void resetAttackHitArray(); //can be called to remove all entries into the array, meaning enemies can be hit again


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void onSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackVariables)
		TArray<AActor*> hitThisAttack; //array storing actors that have been hit by the current attack - stops enemies taking damage from one attack multiple times
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackVariables)
	//TArray<AActor*> hitThisAttack; //array storing actors that have been hit by the current attack - stops enemies taking damage from one attack multiple times

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
