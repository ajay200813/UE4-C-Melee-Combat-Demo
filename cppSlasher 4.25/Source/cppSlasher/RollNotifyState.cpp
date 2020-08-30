// Fill out your copyright notice in the Description page of Project Settings.


#include "RollNotifyState.h"
#include "cppSlasherCharacter.h"
//#include "Runtime/Engine/Public/EngineGlobals.h"

void URollNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AcppSlasherCharacter* playerChar = Cast<AcppSlasherCharacter>(MeshComp->GetOwner());
		if (playerChar != NULL)
		{
				//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, TEXT("Can't now roll!"));
				playerChar->canRoll = false;
				playerChar->canAttack = false;
				playerChar->canBlock = false;
				playerChar->startRotatingWithLimit();
				playerChar->StopSprinting();
		}
	}
}

void URollNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AcppSlasherCharacter* playerChar = Cast<AcppSlasherCharacter>(MeshComp->GetOwner());
		if (playerChar != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, TEXT("Can now roll!"));
			playerChar->canRoll = true;
			playerChar->canAttack = true;
			playerChar->canBlock = true;
			playerChar->shouldRotate = false;
		
		}
	}
}
