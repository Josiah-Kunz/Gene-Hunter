// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Priority_High_DoublePoints_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENTUNITTESTS_API UDoublePoints_High_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	virtual void InitializeEffect() override
	{
		// Get AffinitiesComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UAffinitiesComponent, AffinitiesComponent, GetOwner(), true)

		// Guard
		if (AffinitiesComponent == nullptr)
		{
			return;
		}

		// Soopah doopah
		Super::InitializeEffect();

		// Bind the delegate
		BIND_DELEGATE(Delegate, UDoublePoints_High_UNITTEST::DoublePoints);

		// Add it
		AffinitiesComponent->GetUnspentPointsOutlet.AddBefore(Delegate);
	}

	UPROPERTY()
	UAffinitiesComponent* AffinitiesComponent;

	UPROPERTY()
	FBeforeGetUnspentPointsDelegate Delegate;

	UFUNCTION()
	void DoublePoints(const uint8 OriginalPoints, uint8& ReturnedPoints)
	{
		if (ShouldApplyEffect())
		{
			ReturnedPoints = 2*OriginalPoints;
		}
	}

	// Custom priority things. Normally, you wouldn't do this.
	// -------------------------------------------------------
	
	virtual float GetPriority() override
	{
		return 1;
	}

};
