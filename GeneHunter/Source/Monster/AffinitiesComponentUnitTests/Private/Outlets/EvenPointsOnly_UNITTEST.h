// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "EvenPointsOnly_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AFFINITIESCOMPONENTUNITTESTS_API UEvenPointsOnly_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	virtual void OnComponentCreated() override
	{
		// Get AffinitiesComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UAffinitiesComponent, AffinitiesComponent, GetOwner(), true)

		// Guard
		if (AffinitiesComponent == nullptr)
		{
			return;
		}

		// Soopah doopah
		Super::OnComponentCreated();

		// Bind the delegate
		BIND_DELEGATE(Delegate, UEvenPointsOnly_UNITTEST::RestrictPointsToEven);

		// Add it
		AffinitiesComponent->SetUnspentPointsOutlet.AddBefore(Delegate);
	}

	UPROPERTY()
	UAffinitiesComponent* AffinitiesComponent;

	UPROPERTY()
	FBeforeSetUnspentPointsDelegate Delegate;

	UFUNCTION()
	void RestrictPointsToEven(const uint8 OriginalPoints, const uint8 InputPoints, uint8& SetPoints)
	{
		if (InputPoints % 2 != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tried to set points to [%i], but only even values are allowed! Resetting to original points [%i]."),
				SetPoints,
				OriginalPoints
				)
			SetPoints = OriginalPoints;
		}
	}

};
