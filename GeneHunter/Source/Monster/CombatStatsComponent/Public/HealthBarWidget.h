// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSTATSCOMPONENT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	UCombatStatsComponent* StatsComponent;

	virtual void NativeConstruct() override;

	// Left blank here so that the BP can fill it in.
	virtual void UpdateHealth(){};

private:

	UPROPERTY()
	FAfterModifyStatDelegate AfterModifyStat;

	UFUNCTION()
	void UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OGValue, float& AttemptedValue);
	
};
