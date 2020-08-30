// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRestoreCollisionNotify.h"
#include "enemyNPC.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void UBossRestoreCollisionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AenemyNPC* npc = Cast<AenemyNPC>(MeshComp->GetOwner());
	if (npc != NULL )
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
		npc->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
		npc->canHitPlayer = false;
		npc->attackPower = 20.f;
	}
}