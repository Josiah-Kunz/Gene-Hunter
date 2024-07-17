// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GHLibraries/Public/ComponentUtilities.h"

UHealthBar::UHealthBar()
{
	PrimaryComponentTick.bCanEverTick = false;

	
	
}

void UHealthBar::OnComponentCreated()
{
	Super::OnComponentCreated();

	// Assign stats
	UCombatStatsComponent* StatsComponent = GetOwner()->FindComponentByClass<UCombatStatsComponent>();
	if (!StatsComponent)
	{
		return;
	}
	HealthStat = StatsComponent->GetStat(EStatEnum::Health);

	

	// Construct widgets
	
	//MainBar = CreateWidget<UUserWidget, AActor*>(GetOwner(), ProgressBarClass);
	UWidgetComponent* WidgetComponent = nullptr;
	REQUIRE_COMPONENT(UWidgetComponent, WidgetComponent, GetOwner())
	WidgetComponent->SetWidgetClass(UProgressBar::StaticClass());
	//WidgetComponent->SetWidgetClass();
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetWorldLocation(FVector(0, 0, 0));
	WidgetComponent->SetupAttachment(GetOwner()->GetRootComponent());
	WidgetComponent->SetVisibility(true);
	WidgetComponent->RegisterComponent();
	
	//UWidgetComponent* WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Health Bar - Main");
	/*WidgetComponent->SetWidgetClass(UProgressBar::StaticClass());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetWorldLocation(FVector(0, 0, 0));
	WidgetComponent->SetupAttachment(GetOwner()->GetRootComponent());
	WidgetComponent->SetVisibility(true);
	WidgetComponent->RegisterComponent();
	*/
	
}

void UHealthBar::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthBar::SetMainBar()
{
	
}

