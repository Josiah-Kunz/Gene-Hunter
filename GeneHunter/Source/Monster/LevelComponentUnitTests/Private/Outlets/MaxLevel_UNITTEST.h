// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/GetMaxLevelOutlet.h"
#include "MaxLevel_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UMaxLevel_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeGetMaxLevelDelegate Delegate;

	static constexpr int32 NewMaxLevel = 150;

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
		Delegate.Delegate.BindDynamic(this, &UMaxLevel_UNITTEST::SetMaxLevel);

		// Add it
		LevelComponent->GetMaxLevelOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void SetMaxLevel(const uint16 DefaultMax, int32& AttemptedMax)
	{
		AttemptedMax = NewMaxLevel;
	}

	

};
