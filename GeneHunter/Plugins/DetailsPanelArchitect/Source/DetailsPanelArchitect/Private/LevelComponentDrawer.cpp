#define LOCTEXT_NAMESPACE "LevelComponentDrawer"

#include "LevelComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "SStatsBar.h"
#include "StatsComponentDrawer.h"
#include "Kismet/KismetSystemLibrary.h"

#pragma region Boilerplate

TSharedRef<IDetailCustomization> LevelComponentDrawer::MakeInstance()
{
	return MakeShareable(new LevelComponentDrawer);
}

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
						const int NewLevel = UUtilityFunctionLibrary::FromSI(InText);
						if (NewLevel == LevelComponent->GetLevel())
							return;
						if (UserCommitted(InTextCommit))
							LevelComponent->SetLevel(NewLevel);
						SaveAndRefresh(DetailBuilder);
					})
				.MaxText(FText::FromString(FString::FromInt(LevelComponent->MaxLevel())))
				.MaxTooltip(FText::FromString(FString::FromInt(LevelComponent->MaxLevel())))
				.BarColor(FLinearColor::Green)
				.BarFraction((1.0f * LevelComponent->GetLevel())/LevelComponent->MaxLevel())
				.BarTooltip(FText::FromString(
					FString::Printf(TEXT(
					"The higher the level, the stronger the stats! The max level is %s."),
					*FString::FromInt(LevelComponent->MaxLevel())
					)))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
				TAttribute<bool>::CreateLambda([this]() 
				{ 
					return LevelComponent->GetLevel() != 1;
				}), 
				FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
				{ 
					LevelComponent->SetLevel(1);
					DetailBuilder.ForceRefreshDetails();
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
			.TextBoxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetLevelExp(), StatsComponentDrawer::SigFigs, true))
			.OnTextCommitted([this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Check if anything happened
					const int DiffXP = UUtilityFunctionLibrary::FromSI(InText) - LevelComponent->GetLevelExp();
					if (DiffXP == 0)
						return;

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(LevelComponent->GetLevelExp(), StatsComponentDrawer::SigFigs, true)))
						return;

					// Use did something
					if (UserCommitted(CommitType))
						LevelComponent->AddExp(DiffXP);

					// Refresh either way
					SaveAndRefresh(DetailBuilder);
					//DetailBuilder.ForceRefreshDetails();
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
			TEXT("%s"),
				*FloatToFText(LevelComponent->GetLevelExp(), true).ToString()
				)))
			.MaxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetTotalLevelExp(), StatsComponentDrawer::SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("%s"),
				*FloatToFText(LevelComponent->GetTotalLevelExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.878f, 0.690f, 1.0f, 1.0f})
			.BarFraction(LevelComponent->GetLevelExp()/LevelComponent->GetTotalLevelExp())
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([this]() 
					{ 
						return LevelComponent->GetCumulativeExp() != LevelComponent->GetCumulativeExpFromLevel(LevelComponent->GetLevel());
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						LevelComponent->SetCumulativeExp(LevelComponent->GetCumulativeExpFromLevel(LevelComponent->GetLevel()));
						DetailBuilder.ForceRefreshDetails();
					})
				))
	;
}

void LevelComponentDrawer::CustomizeCXPDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
	FName(LevelCategoryName),
	FText::FromString(LevelCategoryName),
	ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "CXP")).WholeRowContent()[
		SNew(SStatsBar)
			.LabelText(FText::FromString("CXP"))
			.LabelTooltip(FText::FromString("Cumulative experience points"))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetCumulativeExp(), StatsComponentDrawer::SigFigs, true))
			.OnTextCommitted(
				[this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(LevelComponent->GetCumulativeExp(), StatsComponentDrawer::SigFigs, true)))
						return;

					// Change depending on commit type (might have hit "esc", so no changes)
					if (UserCommitted(CommitType))
						LevelComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));

					// Refresh either way
					SaveAndRefresh(DetailBuilder);
					//DetailBuilder.ForceRefreshDetails();
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
					TEXT("%s"),
					*FloatToFText(LevelComponent->GetCumulativeExp(), true).ToString()
					)))
			.MaxText(UUtilityFunctionLibrary::ToSI(LevelComponent->GetMaxExp(), StatsComponentDrawer::SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("Max cumulative exp at level %i is %s."),
				LevelComponent->MaxLevel(),
				*FloatToFText(LevelComponent->GetMaxExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.5f, 0, 0.5f})
			.BarFraction(LevelComponent->GetCumulativeExp()/LevelComponent->GetMaxExp())
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([this]() 
					{ 
						return LevelComponent->GetCumulativeExp() != LevelComponent->GetCumulativeExpFromLevel(LevelComponent->MinLevel());
						
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						LevelComponent->SetCumulativeExp(0);
						DetailBuilder.ForceRefreshDetails();
					})
				))
	;
}

#pragma endregion

#pragma region Public utility functions

void LevelComponentDrawer::SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const
{
	UE_LOG(LogTemp, Warning, TEXT("Saved %s"), *LevelComponent->GetName())
	UKismetSystemLibrary::TransactObject(LevelComponent);
	DetailBuilder.ForceRefreshDetails();
}

bool LevelComponentDrawer::UserCommitted(const ETextCommit::Type CommitType)
{
	return CommitType == ETextCommit::Type::OnEnter || CommitType == ETextCommit::Type::OnUserMovedFocus;
}

#pragma endregion

#pragma region Private utility functions

ULevelComponent* LevelComponentDrawer::GetLevelComponent(const IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	const TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	ULevelComponent* Ret = Cast<ULevelComponent>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;
	UE_LOG(LogTemp, Warning, TEXT("NOT returning nullptr"))
	// Return
	return Ret;
}

FText LevelComponentDrawer::FloatToFText(const float Value, const bool bIntegerOnly)
{
	return FText::FromString(
		bIntegerOnly ?
		FString::FromInt(FMath::RoundToInt(Value)) :
		FString::SanitizeFloat(Value));
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
