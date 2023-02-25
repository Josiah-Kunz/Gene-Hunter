// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/SetBaseExpYieldOutlet.h"
#include "UnchangeableBaseYield_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UUnchangeableBaseYield_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeSetBaseExpYieldDelegate Delegate;

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
		BIND_DELEGATE(Delegate, UUnchangeableBaseYield_UNITTEST::IncreaseExpYield);

		// Add it
		LevelComponent->SetBaseExpYieldOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void IncreaseExpYield(const float OldYield, const float InputYield, float& AttemptedYield)
	{
		AttemptedYield = OldYield;
	}

	

};
