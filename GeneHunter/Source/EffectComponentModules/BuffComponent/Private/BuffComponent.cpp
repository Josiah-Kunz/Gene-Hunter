// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"


// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UBuffComponent::IsPurgeable() const
{
	return true;
}

bool UBuffComponent::IsVisibleToUI() const
{
	return true;
}


