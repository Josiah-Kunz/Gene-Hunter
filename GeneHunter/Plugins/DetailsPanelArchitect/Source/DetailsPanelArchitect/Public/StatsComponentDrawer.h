#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "StatsComponent.h"

class StatsComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	const float Padding = 2;
	const float MaxWidth = 125;
	const float MaxHeight = 20;

#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

#pragma region Private functions
	
private:
	
	UStatsComponent* GetStatsComponent(IDetailLayoutBuilder& DetailBuilder);

	static float MaxStat (const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);

	static void SetStatFromString(FStat* Stat, const FText Text, const EStatValueType StatType);

#pragma endregion
	
};
