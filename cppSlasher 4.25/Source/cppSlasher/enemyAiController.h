// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "enemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class CPPSLASHER_API AenemyAiController : public AAIController
{
	GENERATED_BODY()
public:
	AenemyAiController(FObjectInitializer const& object_init = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;

	
	class UBlackboardComponent* get_Blackboard() const;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behaviourTreeComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* behaviourTree;
	
	class UBlackboardComponent* blackBoard;
};
