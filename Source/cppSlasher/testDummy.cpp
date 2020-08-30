// Fill out your copyright notice in the Description page of Project Settings.


#include "testDummy.h"

void AtestDummy::takeDamage(float damageValue,float armourPen)
{
	Super::takeDamage(damageValue,armourPen);
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, "cringe");
}