// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "SE.generated.h"

/**
 * 
 */
UCLASS()
class CPPSLASHER_API USE : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	USE();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float jumpAttackRange = 400.0f;
};
