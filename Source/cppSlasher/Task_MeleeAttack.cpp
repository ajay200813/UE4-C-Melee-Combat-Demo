// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_MeleeAttack.h"
#include "enemyAiController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"

UTask_MeleeAttack::UTask_MeleeAttack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Melee Attack");
}
EBTNodeResult::Type UTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	//AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn());
	
	if (AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn()))
	{
		if (montage_has_finished(npc))
		{
			npc->MeleeAttack();
			controller->get_Blackboard()->SetValueAsBool(bb_keys::is_in_melee_range,false);
		}
	}
	
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
bool UTask_MeleeAttack::montage_has_finished(AenemyNPC * const npc)
{
	//return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
	return !npc->GetMesh()->GetAnimInstance()->Montage_IsPlaying(npc->GetMontage());
}
