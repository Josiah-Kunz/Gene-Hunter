﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ComponentUtilities.h"		// For ADD_COMPONENT macro
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "LevelComponent.h"
#include "EffectComponent.h"
#include "Outlets/GetMinLevelOutlet.h"
#include "MinLevel_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UMinLevel_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeGetMinLevelDelegate Delegate;

	static constexpr int32 NewMinLevel = 10;

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
		BIND_DELEGATE(Delegate, UMinLevel_UNITTEST::SetMinLevel);

		// Add it
		LevelComponent->GetMinLevelOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void SetMinLevel(const uint16 DefaultMin, int32& AttemptedMin)
	{
		if (ShouldApplyEffect())
		{
			AttemptedMin = NewMinLevel;
		}
	}

	

};
