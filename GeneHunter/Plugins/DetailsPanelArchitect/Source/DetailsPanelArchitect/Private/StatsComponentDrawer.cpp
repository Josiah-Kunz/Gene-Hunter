#define LOCTEXT_NAMESPACE "StatsComponentDrawer"

#include "StatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"
#include "Brushes/SlateImageBrush.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Images/SImage.h"
#include "SStatsBar.h"

TSharedRef<IDetailCustomization> StatsComponentDrawer::MakeInstance()
{
	return MakeShareable(new StatsComponentDrawer);
}

void StatsComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	StatsComponent = GetStatsComponent(DetailBuilder);

	// Details
	CustomizeLevelDetails(DetailBuilder);
	CustomizeExpDetails(DetailBuilder);
	CustomizeCXPDetails(DetailBuilder);
	CustomizeCurrentStatsDetails(DetailBuilder);
	CustomizeBaseStatsDetails(DetailBuilder);
	CustomizeBasePairsDetails(DetailBuilder);
}

void StatsComponentDrawer::CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder)
{

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(LevelCategoryName),
		FText::FromString(LevelCategoryName),
		ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "Level")).WholeRowContent()[
			SNew(SStatsBar)
				.LabelText(FText::FromString("Lv."))
				.LabelTooltip(FText::FromString("Level"))
				.TextBoxText(FText::FromString(FString::FromInt(StatsComponent->GetLevel())))
				.TextBoxTooltip(FText::FromString(FString::Printf(TEXT("%i"), StatsComponent->GetLevel())))
				.OnTextCommitted([this, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
					{
						const int NewLevel = UUtilityFunctionLibrary::FromSI(InText);
						if (NewLevel == StatsComponent->GetLevel())
							return;
						if (UserCommitted(InTextCommit))
							StatsComponent->SetLevel(NewLevel);
						DetailBuilder.ForceRefreshDetails();
					})
				.MaxText(FText::FromString(FString::FromInt(StatsComponent->MaxLevel())))
				.MaxTooltip(FText::FromString(FString::FromInt(StatsComponent->MaxLevel())))
				.BarColor(FLinearColor::Green)
				.BarFraction((1.0f * StatsComponent->GetLevel())/StatsComponent->MaxLevel())
				.BarTooltip(FText::FromString(
					FString::Printf(TEXT(
					"The higher the level, the stronger the stats! The max level is %s."),
					*FString::FromInt(StatsComponent->MaxLevel())
					)))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
				TAttribute<bool>::CreateLambda([]() 
				{ 
					return true;
				}), 
				FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
				{ 
					StatsComponent->SetLevel(1);
					DetailBuilder.ForceRefreshDetails();
				})
			))
	;
}

void StatsComponentDrawer::CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder)
{

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
	FName(LevelCategoryName),
	FText::FromString(LevelCategoryName),
	ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "Exp")).WholeRowContent()[
		SNew(SStatsBar)
			.LabelText(FText::FromString("Exp"))
			.LabelTooltip(FText::FromString("Experience points within the level (non-cumulative experience points)"))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(StatsComponent->GetLevelExp(), SigFigs, true))
			.OnTextCommitted([this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Check if anything happened
					const int DiffXP = UUtilityFunctionLibrary::FromSI(InText) - StatsComponent->GetLevelExp();
					if (DiffXP == 0)
						return;

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetLevelExp(), SigFigs, true)))
						return;

					// Use did something
					if (UserCommitted(CommitType))
						StatsComponent->AddExp(DiffXP);

					// Refresh either way
					DetailBuilder.ForceRefreshDetails();
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
			TEXT("%s"),
				*FloatToFText(StatsComponent->GetLevelExp(), true).ToString()
				)))
			.MaxText(UUtilityFunctionLibrary::ToSI(StatsComponent->GetTotalLevelExp(), SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("%s"),
				*FloatToFText(StatsComponent->GetTotalLevelExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.878f, 0.690f, 1.0f, 1.0f})
			.BarFraction(StatsComponent->GetLevelExp()/StatsComponent->GetTotalLevelExp())
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([]() 
					{ 
						return true;
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						StatsComponent->SetCumulativeExp(StatsComponent->GetCumulativeExpFromLevel(StatsComponent->GetLevel()));
						DetailBuilder.ForceRefreshDetails();
					})
				))
	;
}

void StatsComponentDrawer::CustomizeCXPDetails(IDetailLayoutBuilder& DetailBuilder)
{

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
	FName(LevelCategoryName),
	FText::FromString(LevelCategoryName),
	ECategoryPriority::Important);

	Category.AddCustomRow(LOCTEXT("Keyword", "CXP")).WholeRowContent()[
		SNew(SStatsBar)
			.LabelText(FText::FromString("CXP"))
			.LabelTooltip(FText::FromString("Cumulative experience points"))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs, true))
			.OnTextCommitted(
				[this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs, true)))
						return;

					// Change depending on commit type (might have hit "esc", so no changes)
					if (UserCommitted(CommitType))
						StatsComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));

					// Refresh either way
					DetailBuilder.ForceRefreshDetails();
				})
			.TextBoxTooltip(FText::FromString(FString::Printf(
					TEXT("%s"),
					*FloatToFText(StatsComponent->GetCumulativeExp(), true).ToString()
					)))
			.MaxText(UUtilityFunctionLibrary::ToSI(StatsComponent->GetMaxExp(), SigFigs, true))
			.MaxTooltip(FText::FromString(FString::Printf(
				TEXT("Max cumulative exp at level %i is %s."),
				StatsComponent->MaxLevel(),
				*FloatToFText(StatsComponent->GetMaxExp(), true).ToString()
				)))
			.BarColor(FLinearColor{0.5f, 0, 0.5f})
			.BarFraction(StatsComponent->GetCumulativeExp()/StatsComponent->GetMaxExp())
			.BarTooltip(FText::FromString("Change in exp = change in level"))
			].OverrideResetToDefault(FResetToDefaultOverride::Create( 
					TAttribute<bool>::CreateLambda([]() 
					{ 
						return true;
					}), 
					FSimpleDelegate::CreateLambda([this, &DetailBuilder]() 
					{ 
						StatsComponent->SetCumulativeExp(0);
						DetailBuilder.ForceRefreshDetails();
					})
				))
	;
}

void StatsComponentDrawer::CustomizeCurrentStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	const float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);

	// Construct bars from existing properties
	CURRENT_STAT_PROPERTY(Health, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(Haste, GetCurrentValue(), MaxPercentValue, true)
	CURRENT_STAT_PROPERTY(CriticalHit, GetCurrentValue(), MaxPercentValue, true)
	
}

void StatsComponentDrawer::CustomizeBaseStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::BaseStat, false);
	const float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::BaseStat, true);

	// Get category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName("Base Stats"),
		FText::FromString("Base Stats"),
		ECategoryPriority::Important);

#define HIDE_RESET() \
	FResetToDefaultOverride::Create( \
		TAttribute<bool>::CreateLambda([]() \
		{ \
			return false; \
		}), \
		FSimpleDelegate::CreateLambda([]() {}) \
	)
	
	// Button
	Category.AddCustomRow(LOCTEXT("Keyword", "Base Stat Randomizer Button")).WholeRowContent()[
			SNew(SButton)
				.Text(FText::FromString("Randomize"))
				.ToolTipText(FText::FromString("Randomizes all Base Stats between 80 and 120."))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.TextStyle(FEditorStyle::Get(), "GraphBreadcrumbButtonText")
				.OnClicked_Lambda([this, &DetailBuilder]()
				{
					StatsComponent->RandomizeBaseStats();
					DetailBuilder.ForceRefreshDetails();
					return FReply::Handled();
				})
		].OverrideResetToDefault(HIDE_RESET())
	;
	
	// Construct bars
#define DrawBaseStat(TargetBaseStat, TargetMax) \
	StatWidget(DetailBuilder, Category.AddCustomRow(LOCTEXT("Keyword", "BaseStat")), \
		StatsComponent->##TargetBaseStat, EStatValueType::BaseStat, TargetMax);

	DrawBaseStat(Health, MaxStatValue)
	DrawBaseStat(PhysicalAttack, MaxStatValue)
	DrawBaseStat(PhysicalDefense, MaxStatValue)
	DrawBaseStat(SpecialAttack, MaxStatValue)
	DrawBaseStat(SpecialDefense, MaxStatValue)
	DrawBaseStat(Haste, MaxPercentValue)
	DrawBaseStat(CriticalHit, MaxPercentValue)

	// Base stat total
	Category.AddCustomRow(LOCTEXT("Keyword", "Base Stat Total")).WholeRowContent()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
	[
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
					TEXT("BST: %i       EBSA: %i"),
					FMath::RoundToInt(StatsComponent->BaseStatTotal()),
					FMath::RoundToInt(StatsComponent->BaseStatEffectiveAverage())
				)))
			.TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "SmallText"))
			.ToolTipText(FText::FromString("Base Stat Total and Effective Base Stat Average"))
			.ColorAndOpacity(FLinearColor{1, 1, 1, 0.5f})
	].OverrideResetToDefault(HIDE_RESET())
	;
}

void StatsComponentDrawer::CustomizeBasePairsDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::BasePairs, false);

	// Get category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName("Base Pairs"),
		FText::FromString("Base Pairs"),
		ECategoryPriority::Important);
	
	// Button
	Category.AddCustomRow(LOCTEXT("Keyword", "Base Pair Randomizer Button")).WholeRowContent()[
			SNew(SButton)
				.Text(FText::FromString("Randomize"))
				.ToolTipText(FText::FromString("Randomizes all Base Pairs between 1 and 100."))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.TextStyle(FEditorStyle::Get(), "GraphBreadcrumbButtonText")
				.OnClicked_Lambda([this, &DetailBuilder]()
				{
					StatsComponent->RandomizeBasePairs();
					DetailBuilder.ForceRefreshDetails();
					return FReply::Handled();
				})
		].OverrideResetToDefault(HIDE_RESET())
	;
	
	// Construct bars
#define DrawBasePairs(TargetBasePairs) \
	StatWidget(DetailBuilder, Category.AddCustomRow(LOCTEXT("Keyword", "BasePairs")), \
		StatsComponent->##TargetBasePairs, EStatValueType::BasePairs, MaxStatValue);

	DrawBasePairs(Health)
	DrawBasePairs(PhysicalAttack)
	DrawBasePairs(PhysicalDefense)
	DrawBasePairs(SpecialAttack)
	DrawBasePairs(SpecialDefense)
	DrawBasePairs(Haste)
	DrawBasePairs(CriticalHit)
}

UStatsComponent* StatsComponentDrawer::GetStatsComponent(IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	UStatsComponent* Ret = Cast<UStatsComponent>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;

	// Return
	return Ret;
}

bool StatsComponentDrawer::UserCommitted(const ETextCommit::Type CommitType)
{

	return CommitType == ETextCommit::Type::OnEnter || CommitType == ETextCommit::Type::OnUserMovedFocus;
}

FText StatsComponentDrawer::FloatToFText(const float Value, const bool bIntegerOnly)
{
	return FText::FromString(
		bIntegerOnly ?
		FString::FromInt(FMath::RoundToInt(Value)) :
		FString::SanitizeFloat(Value));
}

void StatsComponentDrawer::StatWidget(IDetailLayoutBuilder& DetailBuilder, FDetailWidgetRow& Widget,
	FStat& TargetStat, const EStatValueType StatValueType, const float OverallMaxValue, const bool bPercentage)
{

	// Get the (local) max value
	const float MaxStatValue = StatValueType == EStatValueType::Current ?
					TargetStat.GetValue(EStatValueType::Permanent) :
					TargetStat.GetValue(StatValueType);

	// Set up "on reset" button delegate
	FSimpleDelegate ResetClicked;
	switch(StatValueType)
	{
	case EStatValueType::BaseStat:
		ResetClicked = FSimpleDelegate::CreateLambda([this, &DetailBuilder, &TargetStat]() 
			{
				TargetStat.RandomizeBaseStat();
				StatsComponent->RecalculateStats();
				DetailBuilder.ForceRefreshDetails();
			}
		);
		break;
	case EStatValueType::BasePairs:
		ResetClicked = FSimpleDelegate::CreateLambda([this, &DetailBuilder, &TargetStat]() 
			{
				TargetStat.RandomizeBasePairs();
				StatsComponent->RecalculateStats();
				DetailBuilder.ForceRefreshDetails();
			}
		);
		break;
	default:
		ResetClicked = FSimpleDelegate::CreateLambda([&DetailBuilder, &TargetStat, MaxStatValue, StatValueType]() 
			{
				TargetStat.ModifyValue(MaxStatValue, StatValueType, EModificationMode::SetDirectly);
				DetailBuilder.ForceRefreshDetails();
			}
		) ;
	}

	// Build widget
	Widget.operator[](
		SNew(SStatsBar)
			.LabelText(FText::FromString(TargetStat.Abbreviation()))
			.LabelTooltip(FText::FromString(TargetStat.Name()))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(TargetStat.GetValue(StatValueType), SigFigs, !bPercentage))
			.TextBoxTooltip(FloatToFText(TargetStat.GetValue(StatValueType), !bPercentage))
			.OnTextCommitted([this, &TargetStat, StatValueType, &DetailBuilder, bPercentage](const FText& InText, const ETextCommit::Type InTextCommit)
				{
					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(TargetStat.GetValue(StatValueType), SigFigs, !bPercentage)))
						return;

					// Check commit method
					if (UserCommitted(InTextCommit))
					{
						TargetStat.ModifyValue( UUtilityFunctionLibrary::FromSI(InText), StatValueType, EModificationMode::SetDirectly);
						switch(StatValueType)
						{
						case EStatValueType::Current:
							break;
						case EStatValueType::Permanent:
							UE_LOG(LogTemp, Error, TEXT("\"Permanent\" not coded for; you should not be able to alter this value directly!"))
							break;
						case EStatValueType::BaseStat:
						case EStatValueType::BasePairs:
							StatsComponent->RecalculateStats(true);
							break;
						case EStatValueType::CurrentAndPermanent:
							UE_LOG(LogTemp, Error, TEXT("\"CurrentAndPermanent\" not coded for; you should not be able to alter this value directly!"))
							break;
						default:
							UE_LOG(LogTemp, Error, TEXT("Unknown case not coded for; you should probably code this!"))
							break;
						}
					}

					// Refresh regardless
					DetailBuilder.ForceRefreshDetails();
				})
			.IsPercentage(bPercentage)
			.MaxText(UUtilityFunctionLibrary::ToSI(MaxStatValue, SigFigs, !bPercentage))
			.MaxTooltip(FloatToFText(MaxStatValue, !bPercentage))
			.BarColor(TargetStat.Color())
			.BarFraction(TargetStat.GetValue(StatValueType) / OverallMaxValue)
			.BarTooltip(TargetStat.SupportingText().Description)
		).OverrideResetToDefault(
			FResetToDefaultOverride::Create( 
				TAttribute<bool>::CreateLambda([]() 
				{ 
					return true;
				}), 
				ResetClicked
			)
		)
	;
}


float StatsComponentDrawer::MaxStat(const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage)
{
	float Max = (bPercentage ? 100 : -INFINITY);
	for(const FStat* Stat : (bPercentage ? StatsComponent->PercentageStats : StatsComponent->NonPercentageStats))
	{

		// Get max depending on what you're after
		switch(StatType)
		{
		case EStatValueType::Current:
			Max = FMathf::Max(Max, Stat->GetCurrentValue());
			break;
		case EStatValueType::Permanent:
			Max = FMathf::Max(Max, Stat->GetPermanentValue());
			break;
		case EStatValueType::CurrentAndPermanent:
			Max = FMathf::Max3(Max, Stat->GetCurrentValue(), Stat->GetPermanentValue());
			break;
		case EStatValueType::BasePairs:
			Max = FMathf::Max3(Max, Stat->BasePairs, 100);
			break;
		case EStatValueType::BaseStat:
			Max = FMathf::Max3(Max, Stat->BaseStat, 120);
			break;
		}
	}
	return Max;
}

void StatsComponentDrawer::SetStatFromString(FStat* Stat, const FText Text, const EStatValueType StatType)
{
	Stat->ModifyValue(FCString::Atof(*Text.ToString()), StatType, EModificationMode::SetDirectly);
}


#undef LOCTEXT_NAMESPACE