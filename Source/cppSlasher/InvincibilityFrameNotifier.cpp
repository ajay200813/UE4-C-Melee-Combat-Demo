// Fill out your copyright notice in the Description page of Project Settings.


#include "InvincibilityFrameNotifier.h"
#include "cppSlasherCharacter.h"

void UInvincibilityFrameNotifier::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AcppSlasherCharacter* playerChar = Cast<AcppSlasherCharacter>(MeshComp->GetOwner());
		if (playerChar != NULL)
		{
			playerChar->isInIFrame = true;

		}
	}
}

void UInvincibilityFrameNotifier::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AcppSlasherCharacter* playerChar = Cast<AcppSlasherCharacter>(MeshComp->GetOwner());
		if (playerChar != NULL)
		{
			playerChar->isInIFrame = false;

		}
	}
}
