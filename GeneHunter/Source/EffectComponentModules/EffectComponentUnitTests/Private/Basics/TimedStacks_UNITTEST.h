// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimedEffectComponent.h"
#include "TimedStacks_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENTUNITTESTS_API UTimedStacks_UNITTEST : public UTimedEffectComponent
{
	GENERATED_BODY()

public:
	virtual int32 MaxStacks() override{return 2;}

};
