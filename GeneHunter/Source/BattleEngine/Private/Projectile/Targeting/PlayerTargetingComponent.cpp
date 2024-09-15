// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTargetingComponent.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlayerTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

FVector UPlayerTargetingComponent::GetAttackVector()
{
	FVector MouseLocation, MouseDirection;
	GetPlayerToMouseVector(MouseLocation, MouseDirection);
	return FVector{MouseDirection.X, MouseDirection.Y, 0};
}

UCombatStatsComponent* UPlayerTargetingComponent::GetTarget()
{

	// Guard
	if (!DoesPCExist())
	{
		return nullptr;
	}
	
	// Set default
	UCombatStatsComponent* TargetStats = Super::GetTarget();

	// Get mouse worlds
	FVector MouseLocation, MouseDirection;
	GetPlayerToMouseVector(MouseLocation, MouseDirection);

	// Get how far we want to raycast
	float TraceDistance = 10000;
	APawn* PlayerPawn = PlayerController->GetPawn();
	FVector CameraLocation;
	if (PlayerPawn)
	{
		UCameraComponent* CameraComponent = PlayerPawn->FindComponentByClass<UCameraComponent>();
		if (CameraComponent)
		{
			CameraLocation = CameraComponent->GetComponentLocation();
            TraceDistance = CameraLocation.Z;
		}
	}
	
	// Set up raycast vars
	//FVector End = MouseLocation + MouseDirection.GetSafeNormal() * TraceDistance;
	const FVector Start = FVector{MouseLocation.X, MouseLocation.Y, -TraceDistance};
	const FVector End = FVector{MouseLocation.X, MouseLocation.Y, TraceDistance};
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	TArray<FHitResult> OutHits;

	// Dewet
	bool bHit = GetWorld()->LineTraceMultiByChannel(
		OutHits, Start, End, ECC_Visibility, TraceParams
	);
	UE_LOG(LogTemp, Warning, TEXT("[%s]--[%s]: [%i] hits"),
			*Start.ToString(),
			*End.ToString(),
			OutHits.Num()
		)
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				// We got stats?
				UCombatStatsComponent* StatsComponent = HitActor->FindComponentByClass<UCombatStatsComponent>();
				if (StatsComponent)
				{
					TargetStats = StatsComponent;
					break; 
				}
			}
		}
	}

	// Optional: Draw the debug line
	if (bHit && TargetStats)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3.0f, 0, 1.0f);
		DrawDebugPoint(GetWorld(), TargetStats->GetOwner()->GetActorLocation(), 10.0f, FColor::Red, false, 3.0f);
	}

	// Return
	return TargetStats;
}

void UPlayerTargetingComponent::GetPlayerToMouseVector(FVector& WorldLocation, FVector& WorldDirection) const
{

	// Guard
	if (!DoesPCExist())
	{
		return;
	}

	// Get mouse world position
	float MouseX, MouseY;
	const bool bMouseExists = PlayerController->GetMousePosition(MouseX, MouseY);
	if (!bMouseExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("No mouse =("))
		return;
	}

	// Project to world
	const bool bCanDetermineValue = PlayerController->DeprojectScreenPositionToWorld(
		MouseX, MouseY, WorldLocation, WorldDirection)
	;
	if (!bCanDetermineValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't determine value =("))
	}
	
}

bool UPlayerTargetingComponent::DoesPCExist() const
{
	const bool bPCExists = PlayerController != nullptr;
	if (!bPCExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s doesn't exist, but it's needed by %s!"),
				*APlayerController::StaticClass()->GetName(),
				*UPlayerTargetingComponent::StaticClass()->GetName()
			)
	}
	return bPCExists;
}
