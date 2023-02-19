// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuffComponent.h"


// Sets default values for this component's properties
UDebuffComponent::UDebuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UDebuffComponent::IsPurgeable() const
{
	return true;
}

bool UDebuffComponent::IsVisibleToUI() const
{
	return true;
}


