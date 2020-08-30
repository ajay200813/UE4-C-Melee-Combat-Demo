// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_ChasePlayer.h"
#include "enemyAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackBoardKeys.h"

UTask_ChasePlayer::UTask_ChasePlayer(FObjectInitializer const& obj_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get TargetLocation from blackboard
	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	FVector const player_location = controller->get_Blackboard()->GetValueAsVector(bb_keys::target_location);

	//move to player location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, player_location);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
