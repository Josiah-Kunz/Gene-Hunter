// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/GetCXPOutlet.h"
#include "Type.h"
#include "AffinitiesComponent.h"

#include "CXPBasedOnType_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENTUNITTESTS_API UCXPBasedOnType_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	float BoostFactor = 1.5f;

	UPROPERTY()
	UType* TypeToBoost;

	UPROPERTY()
	UAffinitiesComponent* AffinitiesComponent;

	UPROPERTY()
	ULevelComponent* LevelComponent;

	UPROPERTY()
	FBeforeGetCXPDelegate Delegate;

	virtual void OnComponentCreated() override
	{
		// Get LevelComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(ULevelComponent, LevelComponent, GetOwner(), true)

		// Get AffinitiesComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UAffinitiesComponent, AffinitiesComponent, GetOwner(), true)

		// Guard
		if (LevelComponent == nullptr || AffinitiesComponent == nullptr)
		{
			return;
		}

		// Soopah doopah
		Super::OnComponentCreated();

		// Bind the delegate
		Delegate.Delegate.BindDynamic(this, &UCXPBasedOnType_UNITTEST::ModifyCXPOnType);

		// Add it
		LevelComponent->GetCXPOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void ModifyCXPOnType(const uint32 OriginalCXP, int32& ReturnedCXP)
	{
		if (AffinitiesComponent->HasPointsAllocatedIn(TypeToBoost))
		{
			ReturnedCXP *= BoostFactor;
		}
	}

	

};
