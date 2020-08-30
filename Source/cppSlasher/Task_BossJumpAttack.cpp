// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_BossJumpAttack.h"
#include "enemyAiController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"

UTask_BossJumpAttack::UTask_BossJumpAttack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Jump Attack");
}
EBTNodeResult::Type UTask_BossJumpAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	//AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn());

	if (AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn()))
	{
		if (montage_has_finished(npc))
		{
			npc->JumpAttack();
			controller->get_Blackboard()->SetValueAsBool(bb_keys::is_in_jump_range,
				false);
		}
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
bool UTask_BossJumpAttack::montage_has_finished(AenemyNPC * const npc)
{
	//return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
	return !npc->GetMesh()->GetAnimInstance()->Montage_IsPlaying(npc->GetJumpMontage());
}