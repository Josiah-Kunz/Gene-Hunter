// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectsManager.h"
#include "EffectComponent.h"


// Sets default values for this component's properties
UEffectsManager::UEffectsManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEffectsManager::OnComponentCreated()
{

	// Super
	Super::OnComponentCreated();

	// Delegate
	const AActor* Owner = GetOwner();
	Owner->

	// Look for existing effects
	GetOwner()->GetComponents<UEffectComponent>(Effects);
}

void UEffectsManager::AddEffect(UEffectComponent* Effect)
{
	Effects.Add(Effect);
}

void UEffectsManager::RemoveEffect(UEffectComponent* Effect)
{
	Effects.Remove(Effect);
}

TArray<UEffectComponent*> UEffectsManager::GetAttachedEffects()
{
	return Effects;
}

