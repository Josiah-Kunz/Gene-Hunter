// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/SetCXPOutlet.h"

#include "CXPLuckyEgg_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UCXPLuckyEgg_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	float BoostFactor = 2.0f;

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeSetCXPDelegate Delegate;

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
		BIND_DELEGATE(Delegate, UCXPLuckyEgg_UNITTEST::ModifyCXPOnSet);

		// Add it
		LevelComponent->SetCXPOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void ModifyCXPOnSet(const uint32 OldCXP, const int32 InputCXP, int32& AttemptedCXP)
	{
		AttemptedCXP = OldCXP + (InputCXP - OldCXP) * GetStacks() * BoostFactor;

	}

	virtual int32 MaxStacks() override
	{
		return 2;
	}

	

};
