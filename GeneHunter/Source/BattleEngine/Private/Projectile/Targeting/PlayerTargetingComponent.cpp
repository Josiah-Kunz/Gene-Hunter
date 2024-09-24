// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTargetingComponent.h"

#include "ComponentUtilities.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"

UPlayerTargetingComponent::UPlayerTargetingComponent(): HUD(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerTargetingComponent::BeginPlay()
{

	// Supah
	Super::BeginPlay();

	// Get HUD
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController){
		HUD = Cast<AWorldHUD>(PlayerController->GetHUD());
	}

	// Get OverlapTracker
	if (!OverlapTracker)
	{
		SEARCH_FOR_COMPONENT_OR_LOG(UOverlapTracker, OverlapTracker, GetOwner())
	}
}

FVector UPlayerTargetingComponent::GetAttackVector()
{
	if (!DoesHUDExist() || OverlapTracker == nullptr)
	{
		return FVector::ZeroVector;
	}
	const FVector MouseDirection = HUD->MouseWorldDirection;
	return FVector{MouseDirection.X, MouseDirection.Y, 0};
}

UCombatStatsComponent* UPlayerTargetingComponent::GetTarget()
{

	// Guard
	if (!OverlapTracker)
	{
		return nullptr;
	}
	
	// Set default
	UCombatStatsComponent* TargetStats = Super::GetTarget();

	// Get the first (non-null) Stats
	TArray<UActorComponent*> StatComponents;
	OverlapTracker->GetOverlappingComponents(UCombatStatsComponent::StaticClass(), StatComponents);
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

void UPlayerTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (HUD)
	{
		const FVector MouseWorld = HUD->MouseWorldLocation;
		OverlapTracker->SetCollisionLocation(MouseWorld);
		
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD missing!"))
	}
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
