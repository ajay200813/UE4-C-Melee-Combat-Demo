// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Animation/AnimMontage.h"
#include "enemyNPC.generated.h"


UCLASS()
class CPPSLASHER_API AenemyNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AenemyNPC();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool canHitPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool isPlayerAlive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float toNextStagger;

	void TurnToFacePlayer();
	void MeleeAttack();
	void JumpAttack();

	UAnimMontage* GetMontage() const;
	UAnimMontage* GetJumpMontage() const;

	ACharacter* playerChar;
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* jumpMontage;
};
