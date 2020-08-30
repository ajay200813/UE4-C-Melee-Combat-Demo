// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "enemyNPC.h"
#include "Task_BossJumpAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPSLASHER_API UTask_BossJumpAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_BossJumpAttack(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	bool montage_has_finished(AenemyNPC* const npc);
};
