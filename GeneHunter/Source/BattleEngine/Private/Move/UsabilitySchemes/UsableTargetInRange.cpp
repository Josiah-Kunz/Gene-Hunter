// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableTargetInRange.h"

void AUsableTargetInRange::Initialize_Implementation(AActor* NewOwner)
{
	Super::Initialize_Implementation(NewOwner);
	Trackers = {};
	for(UActorComponent* Component : NewOwner->K2_GetComponentsByClass(UOverlapTracker::StaticClass()))
	{
		UOverlapTracker* Tracker = Cast<UOverlapTracker>(Component);
		if (Tracker)
		{
			Trackers.Add(Tracker);
		}
	}

	// Surely an error?
	if (Trackers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %s found zero Trackers on %s %s! Make sure you add some to the "
								"Blueprint."),
								*AMoveUsabilityScheme::StaticClass()->GetName(),
								*AUsableTargetInRange::StaticClass()->GetName(),
								*AActor::StaticClass()->GetName(),
								*NewOwner->GetPathName()
								)
	}
}

bool AUsableTargetInRange::IsUsable_Implementation()
{

	// Baseline: are we mousing over anything?
	bool bIsUsable = Super::IsUsable_Implementation();
	if (bIsUsable)
	{
		// This is the Stats we're mousing over
		const UCombatStatsComponent* Target = TargetingComponent->GetTarget();

		// Go through the trackers' overlapping CombatStats and see if it's the one we're mousing over
		for(UOverlapTracker* Tracker : Trackers)
		{
			TArray<UActorComponent*> Components;
			Tracker->GetOverlappingComponents(UCombatStatsComponent::StaticClass(), Components);
			for (UActorComponent* ActorComponent : Components)
			{
				if (ActorComponent)
				{
					const UCombatStatsComponent* TrackedStats = Cast<UCombatStatsComponent>(ActorComponent);
					if (TrackedStats && TrackedStats == Target)
					{
						return true;
					}
				}
			}
		}
	}

	// Must have failed
	return false;
}
