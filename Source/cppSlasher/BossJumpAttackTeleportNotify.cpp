// Fill out your copyright notice in the Description page of Project Settings.


#include "BossJumpAttackTeleportNotify.h"
#include "GameFramework/Character.h"
//#include "cppSlasherCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Engine/World.h"
#include "enemyNPC.h"

void UBossJumpAttackTeleportNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AenemyNPC* npc = Cast<AenemyNPC>(MeshComp->GetOwner());
	//ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
	//AcppSlasherCharacter* player = Cast<AcppSlasherCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (npc != NULL && npc->playerChar != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);
		npc->SetActorLocation(npc->playerChar->GetActorLocation());
		npc->GetCapsuleComponent()->SetCollisionProfileName(TEXT("BossFallAttack"));
		npc->TurnToFacePlayer();
		npc->canHitPlayer = true;
		npc->attackPower = 70.0f;
	}
}