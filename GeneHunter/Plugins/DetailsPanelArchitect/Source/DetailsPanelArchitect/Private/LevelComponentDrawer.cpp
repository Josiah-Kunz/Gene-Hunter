#define LOCTEXT_NAMESPACE "LevelComponentDrawer"

#include "LevelComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"
#include "SStatsBar.h"
#include "CombatStatsComponentDrawer.h"

#pragma region Boilerplate

void LevelComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	LevelComponent = GetLevelComponent(DetailBuilder);

	// Details
	CustomizeLevelDetails(DetailBuilder);
	CustomizeExpDetails(DetailBuilder);
	CustomizeCXPDetails(DetailBuilder);
}

#pragma endregion

#pragma region Private customization functions

void LevelComponentDrawer::CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(LevelCategoryName),
		FText::FromString(LevelCategoryName),
		ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "Level")).WholeRowContent()[
			SNew(SStatsBar)
				.LabelText(FText::FromString("Lv."))
				.LabelTooltip(FText::FromString("Level"))
				.TextBoxText(FText::FromString(FString::FromInt(LevelComponent->GetLevel())))
				.TextBoxTooltip(FText::FromString(FString::Printf(TEXT("%i"), LevelComponent->GetLevel())))
				.OnTextCommitted([this, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
					{
						// Blank text? Just refresh
						if (InText.IsEmptyOrWhitespace())
						{
							SaveAndRefresh(DetailBuilder);
							return;
						}

						// Non-blank; get new level
						const uint16 NewLevel = UUtilityFunctionLibrary::FromSI(InText);
						if (NewLevel == LevelComponent->GetLevel())
							return;
						if (UserCommitted(InTextCommit))
							LevelComponent->SetLevel(NewLevel);
						SaveAndRefresh(DetailBuilder);
					})
				.MaxText(FText::FromString(FString::FromInt(LevelComponent->GetMaxLevel())))
				.MaxTooltip(FText::FromString(FString::FromInt(LevelComponent->GetMaxLevel())))
				.BarColor(FLinearColor::Green)
				.BarFraction(GetFraction(LevelComponent->GetLevel(), LevelComponent->GetMaxLevel()))
				.BarTooltip(FText::FromString(
					FString::Printf(TEXT(
					"The higher the level, the stronger the stats! The max level is %s."),
					*FString::FromInt(LevelComponent->GetMaxLevel())
					)))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
				TAttribute<bool>::CreateLambda([this]() 
				{ 
					return LevelComponent->GetLevel() != 1;
				}), 
				FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
				{ 
					LevelComponent->SetLevel(1);
					SaveAndRefresh(DetailBuilder);
				})
			))
	;
}

void LevelComponentDrawer::CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
	FName(LevelCategoryName),
	FText::FromString(LevelCategoryName),
	ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "Exp")).WholeRowContent()[
		SNew(SStatsBar)
			.LabelText(FText::FromString("Exp"))
			.LabelTooltip(FText::FromString("Experience points within the level (non-cumulative experience points)"))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetLevelExp(), CombatStatsComponentDrawer::SigFigs, true))
			.OnTextCommitted([this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Blank text? Just refresh
					if (InText.IsEmptyOrWhitespace())
					{
						SaveAndRefresh(DetailBuilder);
						return;
					}
				
					// Check if anything happened
					const uint32 DiffXP = UUtilityFunctionLibrary::FromSI(InText) - LevelComponent->GetLevelExp();
					if (DiffXP == 0)
					{
						return;
					}

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(LevelComponent->GetLevelExp(), CombatStatsComponentDrawer::SigFigs, true)))
						return;

					// Use did something
					if (UserCommitted(CommitType))
						LevelComponent->AddExp(DiffXP);

					// Refresh either way
					SaveAndRefresh(DetailBuilder);
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
			TEXT("%s"),
				*FloatToFText(LevelComponent->GetLevelExp(), true).ToString()
				)))
			.MaxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetTotalLevelExp(), CombatStatsComponentDrawer::SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("%s"),
				*FloatToFText(LevelComponent->GetTotalLevelExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.878f, 0.690f, 1.0f, 1.0f})
			.BarFraction(GetFraction(LevelComponent->GetLevelExp(), LevelComponent->GetTotalLevelExp()))
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([this]() 
					{ 
						return LevelComponent->GetCXP() != LevelComponent->GetCXPFromLevel(LevelComponent->GetLevel());
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						LevelComponent->SetCXP(LevelComponent->GetCXPFromLevel(LevelComponent->GetLevel()));
						SaveAndRefresh(DetailBuilder);
					})
				))
	;
}

void LevelComponentDrawer::CustomizeCXPDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
	FName(LevelCategoryName),
	FText::FromString(LevelCategoryName),
	ECategoryPriority::Default);

	Category.AddCustomRow(LOCTEXT("Keyword", "CXP")).WholeRowContent()[
		SNew(SStatsBar)
			.LabelText(FText::FromString("CXP"))
			.LabelTooltip(FText::FromString("Cumulative experience points"))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetCXP(), CombatStatsComponentDrawer::SigFigs, true))
			.OnTextCommitted(
				[this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Blank text? Just refresh
					if (InText.IsEmptyOrWhitespace())
					{
						SaveAndRefresh(DetailBuilder);
						return;
					}

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(LevelComponent->GetCXP(), CombatStatsComponentDrawer::SigFigs, true)))
						return;

					// Change depending on commit type (might have hit "esc", so no changes)
					if (UserCommitted(CommitType))
						LevelComponent->SetCXP(UUtilityFunctionLibrary::FromSI(InText));

					// Refresh either way
					SaveAndRefresh(DetailBuilder);
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
					TEXT("%s"),
					*FloatToFText(LevelComponent->GetCXP(), true).ToString()
					)))
			.MaxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetMaxExp(), CombatStatsComponentDrawer::SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("Max cumulative exp at level %i is %s."),
				LevelComponent->GetMaxLevel(),
				*FloatToFText(LevelComponent->GetMaxExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.5f, 0, 0.5f})
			.BarFraction(GetFraction(LevelComponent->GetCXP(), LevelComponent->GetMaxExp()))
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([this]() 
					{ 
						return LevelComponent->GetCXP() != LevelComponent->GetCXPFromLevel(LevelComponent->GetMinLevel());
						
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						LevelComponent->SetCXP(0);
						SaveAndRefresh(DetailBuilder);
					})
				))
	;
}

#pragma endregion

#pragma region Public utility functions

bool LevelComponentDrawer::UserCommitted(const ETextCommit::Type CommitType)
{
	return CommitType == ETextCommit::Type::OnEnter || CommitType == ETextCommit::Type::OnUserMovedFocus;
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
