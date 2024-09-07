// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * A way to link the WB_Healthbar to C++. Please remember to set the CombatStatsComponent via Blueprints! I've tried to
 * autofind it in NativeInitialize, etc., but it initializes too early (having GameInstance as the outer object).
 */
UCLASS()
class COMBATSTATSCOMPONENT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void InitializeStats();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintType, BlueprintNativeEvent)
	/**
	 *	Set the CombatStatsComponent and updates the UI with the new health.
	 */
	void SetCombatStats(UCombatStatsComponent* NewCombatStats);

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintType, BlueprintNativeEvent, BlueprintPure)
	UCombatStatsComponent* GetCombatStats();
	
	// Left blank here so that the BP can fill it in.
	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintType, BlueprintNativeEvent)
	void UpdateHealth();

private:

	UPROPERTY()
	FAfterModifyStatDelegate AfterModifyStat;

	UFUNCTION()
	void UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OGValue, const float NewValue);

	UPROPERTY(EditAnywhere, Category = "Stats")
	UCombatStatsComponent* StatsComponent;

	bool bStatsIsValid, bStatsInitialized;
	
};
