// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUsabilityScheme.h"

void UMoveUsabilityScheme::Initialize_Implementation(AActor* NewOwner)
{
	Owner = NewOwner;
}

bool UMoveUsabilityScheme::IsUsable_Implementation(AActor* MoveOwner)
{
	return true;
}
