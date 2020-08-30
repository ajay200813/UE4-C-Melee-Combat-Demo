// Fill out your copyright notice in the Description page of Project Settings.


#include "Serv_CheckPlayerIsAlive.h"
#include "enemyAiController.h"
#include "enemyNPC.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "cppSlasherCharacter.h"
#include "BlackBoardKeys.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
UServ_CheckPlayerIsAlive::UServ_CheckPlayerIsAlive()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player Still Alive?");
}

void UServ_CheckPlayerIsAlive::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn());

	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, FString::Printf(TEXT("Bool: %s"), !(npc->isPlayerAlive) ? TEXT("player dead") : TEXT("player alive")));
	controller->get_Blackboard()->SetValueAsBool(bb_keys::player_dead, !(npc->isPlayerAlive));
	

	

}