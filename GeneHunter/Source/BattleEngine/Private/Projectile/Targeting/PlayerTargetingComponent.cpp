// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTargetingComponent.h"

#include "Kismet/GameplayStatics.h"

void UPlayerTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController){
		HUD = Cast<AWorldHUD>(PlayerController->GetHUD());
	}
}

FVector UPlayerTargetingComponent::GetAttackVector()
{
	if (!DoesHUDExist())
	{
		return FVector::ZeroVector;
	}
	const FVector MouseDirection = HUD->MouseWorldDirection;
	return FVector{MouseDirection.X, MouseDirection.Y, 0};
}

UCombatStatsComponent* UPlayerTargetingComponent::GetTarget()
{

	// Guard
	if (!DoesHUDExist())
	{
		return nullptr;
	}
	
	// Set default
	UCombatStatsComponent* TargetStats = Super::GetTarget();

	// Get the first (non-null) Stats
	TArray<UActorComponent*> StatComponents;
	HUD->GetOverlappedComponents(UCombatStatsComponent::StaticClass(), StatComponents);
	for (UActorComponent* Mouseover : StatComponents)
	{
		if (Mouseover)
		{
			UCombatStatsComponent* StatsComponent = Cast<UCombatStatsComponent>(Mouseover);
			if (StatsComponent)
			{
				TargetStats = StatsComponent;
				break;
			}
		}
	}

	// Return
	return TargetStats;
}

bool UPlayerTargetingComponent::DoesHUDExist() const
{
	const bool bPCExists = HUD != nullptr;
	if (!bPCExists)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s doesn't exist, but it's needed by %s! Make sure it's the default HUD in the world settings in-game."),
				*AWorldHUD::StaticClass()->GetName(),
				*UPlayerTargetingComponent::StaticClass()->GetName()
			)
	}
	return bPCExists;
}
