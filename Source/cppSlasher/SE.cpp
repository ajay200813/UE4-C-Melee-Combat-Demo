// Fill out your copyright notice in the Description page of Project Settings.


#include "SE.h"
#include "enemyAiController.h"
#include "enemyNPC.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"

USE::USE()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Jump Attack Range?");
}

void USE::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	controller->get_Blackboard()->SetValueAsBool(bb_keys::is_in_jump_range,
		npc->GetDistanceTo(player) >= jumpAttackRange);

}
