// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAttackNotifyState.h"
#include "enemyNPC.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

//notifies for when the attack colliders should be activated/deactivated during each swing. Attack logic is only active between these notifies.
void UBossAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AenemyNPC* boss = Cast<AenemyNPC>(MeshComp->GetOwner());
		if (boss != NULL)
		{
			boss->TurnToFacePlayer();
			boss->canHitPlayer = true;
		}
	}
}

void UBossAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AenemyNPC* boss = Cast<AenemyNPC>(MeshComp->GetOwner());
		if (boss != NULL)
		{
			boss->canHitPlayer = false;
		}
	}
}