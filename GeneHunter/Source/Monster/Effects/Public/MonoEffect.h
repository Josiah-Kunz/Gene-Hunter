

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonoEffect.generated.h"

/**
 * The base class for so-called "mono" effects. A MonoEffect does one singular thing. An Effect is composed of several
 * MonoEffects.
 */
UCLASS()	// TODO: should this be a struct instead?
class EFFECTS_API UMonoEffect : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
};
