// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "EffectsManager.generated.h"

class UEffectComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UEffectsManager : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TArray<UEffectComponent*> Effects;

public:
	
	UEffectsManager();

	virtual void OnComponentCreated() override;

	UFUNCTION(BlueprintCallable)
	void AddEffect(UEffectComponent* Effect);

	
	UFUNCTION(BlueprintCallable)
	void RemoveEffect(UEffectComponent* Effect);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UEffectComponent*> GetAttachedEffects();
	
};
