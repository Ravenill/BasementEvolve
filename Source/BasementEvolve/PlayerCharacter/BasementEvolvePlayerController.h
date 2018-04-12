// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasementEvolvePlayerController.generated.h"

UCLASS()
class ABasementEvolvePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasementEvolvePlayerController();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player with keyboard */
	void MoveWithKeyboard(float DeltaTime);

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
};


