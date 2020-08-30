// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Serv_CheckPlayerIsAlive.generated.h"

/**
 * 
 */
UCLASS()
class CPPSLASHER_API UServ_CheckPlayerIsAlive : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UServ_CheckPlayerIsAlive();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
