// Fill out your copyright notice in the Description page of Project Settings.


#include "UsabilitySchemes/UsableWithTarget.h"

void AUsableWithTarget::Initialize_Implementation(AActor* NewOwner)
{
	Super::Initialize_Implementation(NewOwner);
	TargetingComponent = NewOwner->FindComponentByClass<UCombatTargetingComponent>();
}

bool AUsableWithTarget::IsUsable_Implementation()
{
	const bool bIsUsable = Super::IsUsable_Implementation();
	return bIsUsable && TargetingComponent->GetTarget() != nullptr;
}
