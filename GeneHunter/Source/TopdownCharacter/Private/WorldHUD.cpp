// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldHUD.h"

#include "ComponentUtilities.h"

void AWorldHUD::GetOverlappedComponents(const TSubclassOf<UActorComponent> ComponentType,
                                        TArray<UActorComponent*>& Components) const
{
	if (!OverlapTracker)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have an attached %s, which is required!"),
				*GetPathName(),
				*UOverlapTracker::StaticClass()->GetName()
			)
	} else if (!OverlapTracker->TrackedComponents.Contains(ComponentType))
	{
		UE_LOG(LogTemp, Warning, TEXT("%p on %s does not currently keep track of %s, but one is being"
			" requested. You can track it by selecting the Blueprint and adding it to its %s UActorComponent."),
			GET_MEMBER_NAME_CHECKED(AWorldHUD, OverlapTracker),
			*GetPathName(),
			*ComponentType->GetName(),
			*UOverlapTracker::StaticClass()->GetName()
			)
	} else
	{
		OverlapTracker->GetOverlappingComponents(ComponentType, Components);
	}
}

void AWorldHUD::BeginPlay()
{
	Super::BeginPlay();
	SEARCH_FOR_COMPONENT(UOverlapTracker, OverlapTracker, this)
	if (!OverlapTracker)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have an attached %s, which is required!"),
				*GetPathName(),
				*UOverlapTracker::StaticClass()->GetName()
			)
	}
}
