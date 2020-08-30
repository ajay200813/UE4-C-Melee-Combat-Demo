// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "enemyAiController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"

UTask_FindRandomLocation::UTask_FindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}
EBTNodeResult::Type UTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_component, uint8* node_memory)
{
	//get AI controller and the NPC
	auto const aiController = Cast<AenemyAiController>(owner_component.GetAIOwner());
	auto const npc = aiController->GetPawn();

	//obtain npc location as starting point
	FVector origin = npc->GetActorLocation();
	FNavLocation location;

	//get nav system and generate a random location on the navmesh
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navSystem->GetRandomPointInNavigableRadius(origin, searchRadius,location,nullptr))
	{
		aiController->get_Blackboard()->SetValueAsVector(bb_keys::target_location, location.Location);
	}
	//finish task with success
	FinishLatentTask(owner_component, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}