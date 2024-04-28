// Copyright 2024 NFB Makes Games. All Rights Reserved.


#include "CameraTrigger.h"
#include "Camera/CameraActor.h"
#include "FollowCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

ACameraTrigger::ACameraTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACameraTrigger::BeginPlay()
{
	// Register delegates
	OnActorBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapEnd);
}

void ACameraTrigger::OnOverlapBegin_Implementation(AActor* ThisActor, AActor* OtherActor)
{
	InitiateCameraUpdate(OtherActor, false);
}

void ACameraTrigger::OnOverlapEnd_Implementation(AActor* ThisActor, AActor* OtherActor)
{
	if (UndoAfterEndOverlap)
	{
		InitiateCameraUpdate(OtherActor, true);
	}
}

void ACameraTrigger::InitiateCameraUpdate_Implementation(AActor* Actor, bool Undo)
{
	if (!Actor) { return; }

	// Only act on actors with a FollowCameraComponent
	UFollowCameraComponent* followCameraComponent = Actor->FindComponentByClass<UFollowCameraComponent>();
	if (!followCameraComponent) { return; }

	// Only act on player-controlled actors
	ACharacter* owner = Cast<ACharacter>(Actor);
	if (!owner) { return; }
	else if (!owner->IsPlayerControlled()) { return; }
	APlayerController* playerController = Cast<APlayerController>(owner->GetController());
	if (!playerController) { return; }

	// Store previous settings, in case of Undo
	if (!Undo)
	{
		PreviousCamera = playerController->GetViewTarget();
		for (const FCameraTriggerUpdateFloat p : FloatParameters)
		{
			FCameraTriggerUpdateFloat update = {
				p.Parameter,
				followCameraComponent->UpdateOrGetFloatParameter(p.Parameter),
				p.BlendTime
			};
			PreviousFloatParameters.Push(update);
		}
		for (const FCameraTriggerUpdateBool p : BoolParameters)
		{
			FCameraTriggerUpdateBool update = {
				p.Parameter,
				followCameraComponent->UpdateOrGetBoolParameter(p.Parameter),
				p.BlendTime
			};
			PreviousBoolParameters.Push(update);
		}
		for (const FCameraTriggerUpdateVector p : VectorParameters)
		{
			FCameraTriggerUpdateVector update = {
				p.Parameter,
				followCameraComponent->UpdateOrGetVectorParameter(p.Parameter),
				p.BlendTime
			};
			PreviousVectorParameters.Push(update);
		}
	}

	// Smoothly blend to new camera, if specified
	AActor* viewTarget = Undo ? PreviousCamera : TargetCamera;
	if (viewTarget) 
	{
		playerController->SetViewTargetWithBlend(
			viewTarget,
			TargetCameraBlendTime,
			VTBlend_EaseInOut,
			1,
			true
		);
	}
	else // If None is specified, return to default FollowCamera at default blend speed
	{
		playerController->SetViewTargetWithBlend(
			owner,
			followCameraComponent->GetDefaultCameraBlendSpeed(),
			VTBlend_EaseInOut,
			1,
			true
		);
	}

	// Update other parameters
	for (int i = 0; i < FloatParameters.Num(); i++)
	{
		FCameraTriggerUpdateFloat update = {
			FloatParameters[i].Parameter,
			Undo ? PreviousFloatParameters[i].Value : FloatParameters[i].Value,
			FloatParameters[i].BlendTime
		};
		followCameraComponent->UpdateOrGetFloatParameter(FloatParameters[i].Parameter, &update);
	}
	for (int i = 0; i < BoolParameters.Num(); i++)
	{
		FCameraTriggerUpdateBool update = {
			BoolParameters[i].Parameter,
			Undo ? PreviousBoolParameters[i].Value : BoolParameters[i].Value,
			BoolParameters[i].BlendTime
		};
		followCameraComponent->UpdateOrGetBoolParameter(BoolParameters[i].Parameter, &update);
	}
	for (int i = 0; i < VectorParameters.Num(); i++)
	{
		FCameraTriggerUpdateVector update = {
			VectorParameters[i].Parameter,
			Undo ? PreviousVectorParameters[i].Value : VectorParameters[i].Value,
			VectorParameters[i].BlendTime
		};
		followCameraComponent->UpdateOrGetVectorParameter(VectorParameters[i].Parameter, &update);
	}
}

