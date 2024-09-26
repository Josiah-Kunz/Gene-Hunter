#include "MouseoverTrigger.h"

#include "ComponentUtilities.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"

void UMouseoverTrigger::SetCollisionComponent(UShapeComponent* NewCollisionComponent)
{

	// Set
	CollisionComponent = NewCollisionComponent;
	
	// Bind events
	CollisionComponent->OnBeginCursorOver.AddDynamic(this, &UMouseoverTrigger::SendMouseoverInfo);
	CollisionComponent->OnEndCursorOver.AddDynamic(this, &UMouseoverTrigger::RetractMouseoverInfo);
}

UMouseoverTrigger::UMouseoverTrigger()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMouseoverTrigger::BeginPlay()
{

	// Supah
	Super::BeginPlay();

	// Get player's targeting component (if any)
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Player)
	{
		SEARCH_FOR_COMPONENT_OR_LOG(UPlayerTargetingComponent, PlayerTargetingComponent, Player);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on %s requires a %s from %s, but none were found!"),
			*UMouseoverTrigger::StaticClass()->GetName(),
			*GetOwner()->GetPathName(),
			*ACharacter::StaticClass()->GetName(),
			*(GET_MEMBER_NAME_CHECKED(UGameplayStatics, GetPlayerCharacter).ToString())
			)
	}

	// Bind?
	if (CollisionComponent)
	{
		SetCollisionComponent(CollisionComponent);
	}
	
}

/**
 * Pls no make const, it won't work with AddDynamic.
 * @param TouchedComponent 
 */
void UMouseoverTrigger::SendMouseoverInfo(UPrimitiveComponent* TouchedComponent)
{
	if (PlayerTargetingComponent)
	{
		AActor* TouchedActor = TouchedComponent->GetOwner();
		if (TouchedActor)
		{
			PlayerTargetingComponent->MouseoverActors.Add(TouchedActor);
			for(UActorComponent* Component : TouchedActor->K2_GetComponentsByClass(UCombatStatsComponent::StaticClass()))
			{
				if (Component)
				{
					UCombatStatsComponent* TouchedStats = Cast<UCombatStatsComponent>(Component);
					if (TouchedStats)
					{
						PlayerTargetingComponent->MouseoverStats.Add(TouchedStats);
					}
				}
			}
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on %s requires a %s!"),
				*UMouseoverTrigger::StaticClass()->GetName(),
				*GetOwner()->GetPathName(),
				*UPlayerTargetingComponent::StaticClass()->GetName()
			)
	}
}

void UMouseoverTrigger::RetractMouseoverInfo(UPrimitiveComponent* TouchedComponent)
{
	AActor* TouchedActor = TouchedComponent->GetOwner();
	if (TouchedActor)
	{
		PlayerTargetingComponent->MouseoverActors.Remove(TouchedActor);
		for(UActorComponent* Component : TouchedActor->K2_GetComponentsByClass(UCombatStatsComponent::StaticClass()))
		{
			if (Component)
			{
				UCombatStatsComponent* TouchedStats = Cast<UCombatStatsComponent>(Component);
				if (TouchedStats)
				{
					PlayerTargetingComponent->MouseoverStats.Remove(TouchedStats);
				}
			}
		}
	}
}

