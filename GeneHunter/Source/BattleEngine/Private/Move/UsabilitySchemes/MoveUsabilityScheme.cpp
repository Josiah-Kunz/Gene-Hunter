// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUsabilityScheme.h"

void AMoveUsabilityScheme::Initialize_Implementation(AActor* NewCaster)
{
	Caster = NewCaster;
	AttachToActor(Caster, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

bool AMoveUsabilityScheme::IsUsable_Implementation()
{
	return true;
}
