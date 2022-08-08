﻿#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "StatsComponent.h"

#include "WidgetParameters/BarWidgetParameters.h"
#include "WidgetParameters/EditableTextBoxWidgetParameters.h"
#include "WidgetParameters/TextWidgetParameters.h"


class StatsComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	inline constexpr static float Padding = 2;
	inline constexpr static float StatInputWidth = 50;
	inline constexpr static float StatAbbrevMaxWidth = 30;
	inline constexpr static float SlashWidth = 10;
	inline constexpr static float ValueMaxWidth = 125;
	inline constexpr static float MaxHeight = 20;
	inline constexpr static int SigFigs = 3;

	const FString LevelCategoryName = "Level";
	
	UStatsComponent* StatsComponent = nullptr;


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

#pragma region Private customization functions

private:
	virtual void CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder);

	virtual void CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder);

	virtual void CustomizeStatsDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UStatsComponent* GetStatsComponent(IDetailLayoutBuilder& DetailBuilder);

	static float MaxStat (const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);

	static void SetStatFromString(FStat* Stat, const FText Text, const EStatValueType StatType);

	void BuildStat(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> PropertyHandle,
		FStat& TargetStat, const EStatValueType StatValueType, const float MaxValue);

	
	void BarWidgetFromNew(

		// Getting the category
		IDetailLayoutBuilder& DetailBuilder, const FString CategoryName,
		FTextWidgetParameters LabelWidgetParameters,
		FEditableTextBoxWidgetParameters EditableTextBoxWidgetParameters,
		FTextWidgetParameters MaxWidgetParameters,
		FBarWidgetParameters BarWidgetParameters,
		TFunction<void (const FText& InText, const ETextCommit::Type InTextCommit)> OnTextCommitted
	);

#pragma endregion
	
};
