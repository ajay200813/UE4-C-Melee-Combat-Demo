// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Task_GetDistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPSLASHER_API UTask_GetDistanceToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_GetDistanceToPlayer(FObjectInitializer const& obj_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:
	float distance; 
};
