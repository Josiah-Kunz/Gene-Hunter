// Fill out your copyright notice in the Description page of Project Settings.


#include "UsabilitySchemes/UsableWithTarget.h"

void UUsableWithTarget::Initialize_Implementation(AActor* NewOwner)
{
	Super::Initialize_Implementation(NewOwner);
	TargetingComponent = NewOwner->FindComponentByClass<UCombatTargetingComponent>();
}

bool UUsableWithTarget::IsUsable_Implementation(AActor* MoveOwner)
{
	const bool bIsUsable = Super::IsUsable_Implementation(MoveOwner);
	return bIsUsable && TargetingComponent->GetTarget() != nullptr;
}
