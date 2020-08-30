// Fill out your copyright notice in the Description page of Project Settings.


#include "Serv_IsPlayerInMeleeRange.h"
//#include "enemyAiController.h"
//#include "enemyNPC.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"

UServ_IsPlayerInMeleeRange::UServ_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Melee Range");
}

void UServ_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AenemyAiController* const controller = Cast<AenemyAiController>(owner_comp.GetAIOwner());
	AenemyNPC* const npc = Cast<AenemyNPC>(controller->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);


	controller->get_Blackboard()->SetValueAsBool(bb_keys::is_in_melee_range,
		npc->GetDistanceTo(player) <= meleeRange);

	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);

}


