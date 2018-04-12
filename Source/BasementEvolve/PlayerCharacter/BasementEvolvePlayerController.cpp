// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BasementEvolvePlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "BasementEvolveCharacter.h"

ABasementEvolvePlayerController::ABasementEvolvePlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::None;
	CurrentMouseCursor = EMouseCursor::None;
}

void ABasementEvolvePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MoveWithKeyboard(DeltaTime);
}

void ABasementEvolvePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//WSAD movement
	InputComponent->BindAxis("MoveX", this, &ABasementEvolvePlayerController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABasementEvolvePlayerController::Move_YAxis);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABasementEvolvePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABasementEvolvePlayerController::MoveToTouchLocation);
}

void ABasementEvolvePlayerController::MoveWithKeyboard(float DeltaTime)
{
	if (ABasementEvolveCharacter* MyPawn = Cast<ABasementEvolveCharacter>(GetPawn()))
	{
		UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetActorLocation() + MyPawn->GetCurrentPlayerVelocity());
	}
}

void ABasementEvolvePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ABasementEvolvePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ABasementEvolvePlayerController::Move_XAxis(float AxisValue)
{
	if (ABasementEvolveCharacter* MyPawn = Cast<ABasementEvolveCharacter>(GetPawn()))
	{
		const float Velocity = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
		MyPawn->SetCurrentPlayerVelocityOnXAxis(Velocity);
	}
}

void ABasementEvolvePlayerController::Move_YAxis(float AxisValue)
{
	if (ABasementEvolveCharacter* MyPawn = Cast<ABasementEvolveCharacter>(GetPawn()))
	{
		const float Velocity = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
		MyPawn->SetCurrentPlayerVelocityOnYAxis(Velocity);
	}
}
