// Fill out your copyright notice in the Description page of Project Settings.


#include "enemyAiController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "cppSlasherCharacter.h"

AenemyAiController::AenemyAiController(FObjectInitializer const& object_init)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> btObj(TEXT("BehaviorTree'/Game/AI/Boss/Boss_BT.Boss_BT'"));
	if (btObj.Succeeded())
	{
		behaviourTree = btObj.Object;
	}
	behaviourTreeComponent = object_init.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviourTreeComponent"));
	blackBoard = object_init.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	
}
void AenemyAiController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behaviourTree);
	behaviourTreeComponent->StartTree(*behaviourTree);
	
}

void AenemyAiController::OnPossess(APawn * const pawn)
{
	Super::OnPossess(pawn);
	if (blackBoard)
	{
		blackBoard->InitializeBlackboard(*behaviourTree->BlackboardAsset);
	}
}



UBlackboardComponent * AenemyAiController::get_Blackboard() const
{
	return blackBoard;
}
