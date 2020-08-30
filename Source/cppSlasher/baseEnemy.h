// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "baseEnemy.generated.h"

UCLASS()
class CPPSLASHER_API AbaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AbaseEnemy();

	UPROPERTY(EditAnywhere)
		USceneComponent* enemyRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* enemyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UCharacterMovementComponent* enemyMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void takeDamage(float damageValue, float armourPen);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float armour;
	

};
