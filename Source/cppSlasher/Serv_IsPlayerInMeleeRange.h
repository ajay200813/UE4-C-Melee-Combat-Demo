// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "enemyAiController.h"
#include "enemyNPC.h"
#include "BehaviorTree/BTService.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Serv_IsPlayerInMeleeRange.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPSLASHER_API UServ_IsPlayerInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UServ_IsPlayerInMeleeRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float meleeRange = 25.0f;

};
