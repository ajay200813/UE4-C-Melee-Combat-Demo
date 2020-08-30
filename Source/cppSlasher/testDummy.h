// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseEnemy.h"
#include "testDummy.generated.h"

/**
 * 
 */
UCLASS()
class CPPSLASHER_API AtestDummy : public AbaseEnemy
{
	GENERATED_BODY()
	
public:
	virtual void takeDamage(float damageValue, float armourPen) override;
};
