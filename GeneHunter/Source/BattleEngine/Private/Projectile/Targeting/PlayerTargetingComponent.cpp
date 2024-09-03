// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTargetingComponent.h"

#include "Kismet/GameplayStatics.h"


UPlayerTargetingComponent::UPlayerTargetingComponent()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

FVector UPlayerTargetingComponent::GetAttackVector()
{
	const FVector2D MouseVector = GetPlayerToMouseVector();
	return FVector{MouseVector.X, MouseVector.Y, 0};
}

FVector2D UPlayerTargetingComponent::GetPlayerToMouseVector() const
{
	
	// Project the actor's world position to screen space
	FVector2D ActorScreenPosition;
	if (!PlayerController->ProjectWorldLocationToScreen(GetOwner()->GetActorLocation(), ActorScreenPosition))
	{
		// Failed projection =(
		return FVector2D::ZeroVector; 
	}

	// Get the mouse cursor's position in screen space
	FVector2D MouseScreenPosition;
	PlayerController->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);

	// Doneeee
	return MouseScreenPosition - ActorScreenPosition;
}
