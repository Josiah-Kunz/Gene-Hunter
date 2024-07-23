// Fill out your copyright notice in the Description page of Project Settings.


#include "DependentComponent.h"


// Sets default values for this component's properties
UDependentComponent::UDependentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDependentComponent::OnRegister()
{
	Super::OnRegister();
	AActor* Owner = GetOwner();

	Stats = Owner->FindComponentByClass<UCombatStatsComponent>();

	if (Stats == nullptr)
	{
		Stats = Owner->GetComponentByClass<UCombatStatsComponent>();
		if (Stats == nullptr)
		{
			Stats = NewObject< UCombatStatsComponent >( Owner ); \
			if ( Stats ){ \
				Owner ->AddInstanceComponent( Stats ); \
				Stats ->RegisterComponent(); \
			}
		}
	}



	
	Indy = Owner->FindComponentByClass<UIndependentComponent>();

	if (Indy == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Find by class failed!"))
		Indy = Owner->GetComponentByClass<UIndependentComponent>();
		if (Indy == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Get by class failed!"))
			Indy = NewObject< UIndependentComponent >( Owner ); \
			if ( Indy ){ \
				Owner ->AddInstanceComponent( Indy ); \
				Indy ->RegisterComponent(); \
			}
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("Get by class succeeded!"))
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find by class succeeded!"))
	}
	Indy->X = 7;
	Indy->Rename(TEXT("I renamed this"));
}


// Called when the game starts
void UDependentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDependentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MsgTime += DeltaTime;
	if (MsgTime > MsgGap)
	{
		MsgTime = 0;

		
		if (Stats == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stats null"))
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Stats fine"))
		}

		
		if (Indy == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Indy null"))
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Indy fine"))
		}
	}
}

