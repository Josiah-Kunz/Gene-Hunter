// Fill out your copyright notice in the Description page of Project Settings.


#include "SCombatProfile.h"

#include "STypePlate.h"
#include "SlateOptMacros.h"
#include "TypeUtilities.h"
#include "WidgetFunctionLibrary.h"
#include "Widgets/Colors/SColorBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCombatProfile::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		MakeSlate(InArgs)
	];
	
}

TSharedRef<SVerticalBox> SCombatProfile::MakeSlate(const FArguments& InArgs)
{
	TSharedRef<SVerticalBox> Ret = SNew(SVerticalBox);
	TArray<UType*> AllTypes;
	UType::GetAllTypes(AllTypes);
	if (InArgs._CombatAnalysisMode == ECombatAnalysisMode::Attack ||
		InArgs._CombatAnalysisMode == ECombatAnalysisMode::Both)
		MakeCombatProfile(InArgs, Ret, true, AllTypes);
	if (InArgs._CombatAnalysisMode == ECombatAnalysisMode::Defense ||
		InArgs._CombatAnalysisMode == ECombatAnalysisMode::Both)
		MakeCombatProfile(InArgs, Ret, false, AllTypes);
		
	return Ret;
}

void SCombatProfile::MakeCombatProfile(const FArguments& InArgs, const TSharedRef<SVerticalBox>& VerticalBox,
	const bool bAtk, const TArray<UType*>& AllTypes)
{

	// Track to see if we drew at least one (we'll use this later)
	bool bDrewOne = false;
	
	for(const TPair<FFloatRange, FString>& RangeLabelPair : UTypeUtilities::EffectivenessLabels(bAtk))
	{
		
		// Do the analysis
		TArray<FTypeArray1D> TypeCombinations, Analysis;
		UTypeUtilities::GetAllTypeCombinations(AllTypes, 1, TypeCombinations);
		UTypeUtilities::Analyze(
			InArgs._Types,
			TypeCombinations,
			RangeLabelPair.Key,
			Analysis,
			EAttackModifierMode::Coverage,
			bAtk
		);

		// If no types, skip
		if (Analysis.Num() == 0)
			continue;
		bDrewOne = true;

		// Header
		VerticalBox->AddSlot()
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(RangeLabelPair.Value))
				.Font(FEditorStyle::GetFontStyle("BoldFont"))
				.TextStyle(FEditorStyle::Get(), "Menu.Heading")
				.ColorAndOpacity(FLinearColor::White)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ShadowOffset(FVector2D{1, 1})
			];

		// Types
		for(int i=0; i<Analysis.Num(); i+=InArgs._TypesPerRow)
		{

			// Create container
			TSharedPtr<SHorizontalBox> Container = SNew(SHorizontalBox);

			// Add stuff
			for(int j=0; j<InArgs._TypesPerRow; j++)
			{	
				Container->AddSlot()
				.AutoWidth()
				.Padding(2)
				.HAlign(HAlign_Center)
				[
					MakeTypeRowWidget(InArgs, Analysis, i+j)
				]
				;
			}

			// Add horizontal box to vertical stack
			VerticalBox->AddSlot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(2)
				[
					Container.ToSharedRef()
				]
			;
		}
	}

	// Didn't draw any =(
	if (!bDrewOne)
		VerticalBox->AddSlot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
			DrawNoCombatProfile()
			]
	;
}

TSharedRef<SWidget> SCombatProfile::MakeTypeRowWidget(const FArguments& InArgs, TArray<FTypeArray1D>& Analysis,
	const int ArrayIndex)
{
	// Check within array range
	if (ArrayIndex >= Analysis.Num())
	{
		return SNew(SOverlay);
	}

	// Build fo rill
	return SNew(STypePlate)
		.Type(Analysis[ArrayIndex].Array[0])
		.Height(InArgs._Height)
		.Width(InArgs._Width)
		.CornerRadius(InArgs._CornerRadius)
	;
}

TSharedRef<SWidget> SCombatProfile::DrawNoCombatProfile() const
{
	return SNew(STextBlock)
			.Text(FText::FromString("All Neutral"))
			.Font(FEditorStyle::GetFontStyle("BoldFont"))
			.TextStyle(FEditorStyle::Get(), "Menu.Heading")
			.ColorAndOpacity(FLinearColor::White)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ShadowOffset(FVector2D{1, 1});
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
