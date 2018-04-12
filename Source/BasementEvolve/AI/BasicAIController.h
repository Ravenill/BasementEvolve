// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAIController.generated.h"

/**
 * 
 */
UCLASS()
class BASEMENTEVOLVE_API ABasicAIController : public AAIController
{
	GENERATED_BODY()
	
private:
    UBehaviorTreeComponent * BehaviorTree;
    //UBlackboardComponent* BlackBoard;

public:
    ABasicAIController();
    ~ABasicAIController();

    virtual void Possess(APawn* Pawn) override;
};
