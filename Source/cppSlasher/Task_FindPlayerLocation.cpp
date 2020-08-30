// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "enemyAiController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
//#include "cppSlasherCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"
UTask_FindPlayerLocation::UTask_FindPlayerLocation(FObjectInitializer const& obj_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent & owner_comp, uint8 * node_memory)
{
	//get player character and AI controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());

	//gets the location of the player character
	FVector const playerLocation = player->GetActorLocation();

	//set as location to move to
	controller->get_Blackboard()->SetValueAsVector(bb_keys::target_location, playerLocation);

	//finish as success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
