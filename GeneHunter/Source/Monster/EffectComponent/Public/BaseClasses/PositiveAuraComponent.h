// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "PositiveAuraComponent.generated.h"


/**
 * A class for positive auras (positive effects that do not expire).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UPositiveAuraComponent : public UEffectComponent
{
	GENERATED_BODY()

public:
	UPositiveAuraComponent();

};
