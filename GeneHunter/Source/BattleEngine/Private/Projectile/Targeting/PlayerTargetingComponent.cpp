// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTargetingComponent.h"

#include "Kismet/GameplayStatics.h"


void UPlayerTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

FVector UPlayerTargetingComponent::GetAttackVector()
{
	const FVector2D MouseVector = GetPlayerToMouseVector();
	return FVector{MouseVector.X, MouseVector.Y, 0};
}

FVector2D UPlayerTargetingComponent::GetPlayerToMouseVector() const
{

	// Get mouse position
	float MouseX, MouseY;
	const bool bMouseExists = PlayerController->GetMousePosition(MouseX, MouseY);
	if (!bMouseExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("No mouse =("))
		return FVector2D::ZeroVector;
	} 
	
	// Project to world
	FVector WorldLocation, WorldDirection;
	const bool bCanDetermineValue = PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);
	if (!bCanDetermineValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't determine value =("))
		return FVector2D::ZeroVector;
	}
	
	// Return
	return FVector2D{WorldDirection.X, WorldDirection.Y};
}
