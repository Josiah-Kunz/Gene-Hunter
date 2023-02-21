// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "Stacks_Single_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENTUNITTESTS_API UStacks_Single_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:
	virtual int32 MaxStacks() override{return 1;}

};
