// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "BehaviorTree\BehaviorTreeComponent.h"
#include "BehaviorTree\BlackboardComponent.h"

ABasicAIController::ABasicAIController()
{
    BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
    Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard")); //may not work, coz it's protected variable from AIController
}

ABasicAIController::~ABasicAIController()
{

}

void ABasicAIController::Possess(APawn * Pawn)
{
    Super::Possess(Pawn);
}
