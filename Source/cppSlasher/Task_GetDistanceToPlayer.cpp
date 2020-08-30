// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_GetDistanceToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "enemyAiController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"


UTask_GetDistanceToPlayer::UTask_GetDistanceToPlayer(FObjectInitializer const& obj_initializer)
{
	NodeName = TEXT("Get Distance To Player");
}

EBTNodeResult::Type UTask_GetDistanceToPlayer::ExecuteTask(UBehaviorTreeComponent & owner_comp, uint8 * node_memory)
{
	//get player character and AI controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	auto const npc = controller->GetPawn();
	//gets the location of the player character
	FVector const playerLocation = player->GetActorLocation();
	FVector const npcLocation = npc->GetActorLocation();
	distance = UKismetMathLibrary::Sqrt(FMath::Square(npcLocation.X - playerLocation.X) + FMath::Square(npcLocation.Y - playerLocation.Y) + FMath::Square(npcLocation.Z - playerLocation.Z));
	controller->get_Blackboard()->SetValueAsFloat(bb_keys::player_distance, distance);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
