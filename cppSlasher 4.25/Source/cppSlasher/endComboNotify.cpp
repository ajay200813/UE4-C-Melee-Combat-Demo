// Fill out your copyright notice in the Description page of Project Settings.


#include "endComboNotify.h"
#include "cppSlasherCharacter.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

void UendComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//used for the final move of a combo to ensure that the player cannot click fast enough to make the combocounter go beyond the number of animations present.
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	AcppSlasherCharacter* playerChar = Cast<AcppSlasherCharacter>(MeshComp->GetOwner());
	if (playerChar != NULL)
	{
		playerChar->comboCounter = 1;
		playerChar->canAttack = true;
		playerChar->canBlock = true;
		playerChar->canRoll = true;
	}
}
