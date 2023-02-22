// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/GetBaseExpYieldOutlet.h"
#include "MoreYield_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UMoreYield_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	virtual void OnComponentCreated() override
	{
		// Get LevelComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(ULevelComponent, LevelComponent, GetOwner(), true)

		// Guard
		if (LevelComponent == nullptr)
		{
			return;
		}

		// Soopah doopah
		Super::OnComponentCreated();

		// Bind the delegate
		Delegate.Delegate.BindDynamic(this, &UMoreYield_UNITTEST::IncreaseExpYield);

		// Add it
		LevelComponent->GetBaseExpYieldOutlet.AddBefore(Delegate);
	}

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeGetBaseExpYieldDelegate Delegate;

	static constexpr float YieldMultiplier = 1.1f;

	UFUNCTION()
	void IncreaseExpYield(const float OriginalYield, float& ReturnedYield)
	{
		ReturnedYield *= YieldMultiplier;
	}

	

};
