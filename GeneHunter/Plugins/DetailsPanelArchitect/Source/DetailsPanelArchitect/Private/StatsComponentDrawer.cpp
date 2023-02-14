#define LOCTEXT_NAMESPACE "CombatStatsComponentDrawer"

#include "CombatStatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"
#include "SStatsBar.h"

#pragma region Boilerplate

void CombatStatsComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	CombatStatsComponent = GetCombatStatsComponent(DetailBuilder);

	// Details
	CustomizeCurrentStatsDetails(DetailBuilder);
	CustomizeBaseStatsDetails(DetailBuilder);
	CustomizeBasePairsDetails(DetailBuilder);
}

#pragma endregion

#pragma region Private customization functions

void CombatStatsComponentDrawer::CustomizeCurrentStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get useful limits
	const float MaxStatValue = MaxStat(CombatStatsComponent, EStatValueType::Current, false);
	const float MaxPercentValue = MaxStat(CombatStatsComponent, EStatValueType::Current, true);

	// Get category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName("Current Stats"),
		FText::FromString("Current Stats"),
		ECategoryPriority::Default);
	
	// Macro for stats (if not for GET_MEMBER_NAME_CHECKED, you could do this as a function
#define CURRENT_STAT_PROPERTY(TargetStat, ValueMember, ValueMax, bPercentage) \
	StatWidget( \
		DetailBuilder, \
		Category.AddCustomRow(LOCTEXT("Keyword", "CurrentStats")), \
		EStatEnum::##TargetStat , \
		EStatValueType::Current, \
		ValueMax, \
		bPercentage);

	// Construct bars from existing properties
	CURRENT_STAT_PROPERTY(Health, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(Haste, GetCurrentValue(), MaxPercentValue, true)
	CURRENT_STAT_PROPERTY(CriticalHit, GetCurrentValue(), MaxPercentValue, true)

	// Set as first category
	DetailBuilder.EditCategory(TEXT("Current Stats")).SetSortOrder(0);
	
}

void CombatStatsComponentDrawer::CustomizeBaseStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get useful limits
	const float MaxStatValue = MaxStat(CombatStatsComponent, EStatValueType::BaseStat, false);
	const float MaxPercentValue = MaxStat(CombatStatsComponent, EStatValueType::BaseStat, true);

	// Get category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName("Base Stats"),
		FText::FromString("Base Stats"),
		ECategoryPriority::Default);

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
				.TextStyle(FAppStyle::Get(), "GraphBreadcrumbButtonText")
				.OnClicked_Lambda([this, &DetailBuilder]()
				{
					CombatStatsComponent->RandomizeBaseStats();
					DetailBuilder.ForceRefreshDetails();
					return FReply::Handled();
				})
		].OverrideResetToDefault(HIDE_RESET())
	;
	
	// Construct bars
#define DRAW_BASE_STAT(TargetBaseStat, TargetMax) \
	StatWidget( \
		DetailBuilder, \
		Category.AddCustomRow(LOCTEXT("Keyword", "BaseStat")), \
		EStatEnum::##TargetBaseStat , \
		EStatValueType::BaseStat, \
		TargetMax \
	);

	DRAW_BASE_STAT(Health, MaxStatValue)
	DRAW_BASE_STAT(PhysicalAttack, MaxStatValue)
	DRAW_BASE_STAT(PhysicalDefense, MaxStatValue)
	DRAW_BASE_STAT(SpecialAttack, MaxStatValue)
	DRAW_BASE_STAT(SpecialDefense, MaxStatValue)
	DRAW_BASE_STAT(Haste, MaxPercentValue)
	DRAW_BASE_STAT(CriticalHit, MaxPercentValue)

	// Base stat total
	Category.AddCustomRow(LOCTEXT("Keyword", "Base Stat Total")).WholeRowContent()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
	[
		SNew(STextBlock)
			.Text(FText::FromString(FString::Printf(
					TEXT("BST: %i       EBSA: %i"),
					FMath::RoundToInt(CombatStatsComponent->BaseStatTotal()),
					FMath::RoundToInt(CombatStatsComponent->BaseStatEffectiveAverage())
				)))
			.TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>( "SmallText"))
			.ToolTipText(FText::FromString("Base Stat Total and Effective Base Stat Average"))
			.ColorAndOpacity(FLinearColor{1, 1, 1, 0.5f})
	].OverrideResetToDefault(HIDE_RESET())
	;
}

void CombatStatsComponentDrawer::CustomizeBasePairsDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get useful limits
	const float MaxStatValue = MaxStat(CombatStatsComponent, EStatValueType::BasePairs, false);

	// Get category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName("Base Pairs"),
		FText::FromString("Base Pairs"),
		ECategoryPriority::Default);
	
	// Button
	Category.AddCustomRow(LOCTEXT("Keyword", "Base Pair Randomizer Button")).WholeRowContent()[
			SNew(SButton)
				.Text(FText::FromString("Randomize"))
				.ToolTipText(FText::FromString("Randomizes all Base Pairs between 1 and 100."))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.TextStyle(FAppStyle::Get(), "GraphBreadcrumbButtonText")
				.OnClicked_Lambda([this, &DetailBuilder]()
				{
					CombatStatsComponent->RandomizeBasePairs();
					DetailBuilder.ForceRefreshDetails();
					return FReply::Handled();
				})
		].OverrideResetToDefault(HIDE_RESET())
	;
	
	// Construct bars
#define DRAW_BASE_PAIRS(TargetBasePairs) \
	StatWidget( \
		DetailBuilder, \
		Category.AddCustomRow(LOCTEXT("Keyword", "BasePairs")), \
		EStatEnum::##TargetBasePairs , \
		EStatValueType::BasePairs, \
		MaxStatValue\
	);
	
	DRAW_BASE_PAIRS(Health)
	DRAW_BASE_PAIRS(PhysicalAttack)
	DRAW_BASE_PAIRS(PhysicalDefense)
	DRAW_BASE_PAIRS(SpecialAttack)
	DRAW_BASE_PAIRS(SpecialDefense)
	DRAW_BASE_PAIRS(Haste)
	DRAW_BASE_PAIRS(CriticalHit)
}

#pragma endregion

#pragma region Public utility functions


TFunction<void(const FText&, ETextCommit::Type&)> CombatStatsComponentDrawer::StatOnTextCommitted(
	IDetailLayoutBuilder& DetailBuilder, const EStatEnum TargetStat,
	const EStatValueType StatValueType, const bool bPercentage) const
{
	return [this, &DetailBuilder, TargetStat, StatValueType, bPercentage]
				(const FText& InText, const ETextCommit::Type InTextCommit)
	{

		// Blank text? Just refresh
		if (InText.IsEmptyOrWhitespace())
		{
			SaveAndRefresh(DetailBuilder);
			return;
		}

		// Check to see if anything changed (avoids rounding errors)
		if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType), SigFigs, !bPercentage)))
			return;

		// Check commit method
		if (this->UserCommitted(InTextCommit))
		{
			// Modify the stat, but see if it is intentional
			CombatStatsComponent->ModifyStat( TargetStat, UUtilityFunctionLibrary::FromSI(InText), StatValueType, EModificationMode::SetDirectly);
			switch(StatValueType)
			{
			case EStatValueType::Current:
				break;
			case EStatValueType::Permanent:
				UE_LOG(LogTemp, Error, TEXT("\"Permanent\" not coded for; you should not be able to alter this value directly!"))
				break;
			case EStatValueType::BaseStat:
			case EStatValueType::BasePairs:
				CombatStatsComponent->RecalculateStats(true);
				break;
			default:
				UE_LOG(LogTemp, Error, TEXT("Unknown case not coded for; you should probably code this!"))
				break;
			}

			// Save
			SaveAndRefresh(DetailBuilder);
		}
	};
}

bool CombatStatsComponentDrawer::UserCommitted(const ETextCommit::Type CommitType)
{
	return CommitType == ETextCommit::Type::OnEnter || CommitType == ETextCommit::Type::OnUserMovedFocus;
}

#pragma endregion

#pragma region Private utility functions

float CombatStatsComponentDrawer::MaxStat(UCombatStatsComponent* CombatStatsComponent, const EStatValueType StatType, const bool bPercentage)
{
	float Max = (bPercentage ? 100 : -INFINITY);
	for(const EStatEnum Stat : (bPercentage ? CombatStatsComponent->PercentageStats : CombatStatsComponent->NonPercentageStats))
	{

		// Get max depending on what you're after
		switch(StatType)
		{
		case EStatValueType::Current:
			Max = FMathf::Max(Max, CombatStatsComponent->GetStat(Stat).GetCurrentValue());
			break;
		case EStatValueType::Permanent:
			Max = FMathf::Max(Max, CombatStatsComponent->GetStat(Stat).GetPermanentValue());
			break;
		case EStatValueType::BasePairs:
			Max = FMathf::Max3(Max, CombatStatsComponent->GetStat(Stat).BasePairs, 100);
			break;
		case EStatValueType::BaseStat:
			Max = FMathf::Max3(Max, CombatStatsComponent->GetStat(Stat).BaseStat, 120);
			break;
		}
	}
	return Max;
}

void CombatStatsComponentDrawer::StatWidget(IDetailLayoutBuilder& DetailBuilder, FDetailWidgetRow& Widget,
	const EStatEnum TargetStat, const EStatValueType StatValueType,
	const float OverallMaxValue, const bool bPercentage) const
{
	
	// Get the (local) max value
	const float MaxStatValue = StatValueType == EStatValueType::Current ?
					CombatStatsComponent->GetStat(TargetStat).GetValue(EStatValueType::Permanent) :
					CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType);

	// Reset button on the far right
	const FSimpleDelegate ResetClicked = CreateResetDelegate(
		DetailBuilder, TargetStat, StatValueType, MaxStatValue);
	
	// Build widget
	Widget.operator[](
		SNew(SStatsBar)
			.LabelText(FText::FromString(CombatStatsComponent->GetStat(TargetStat).Abbreviation()))
			.LabelTooltip(FText::FromString(CombatStatsComponent->GetStat(TargetStat).Name()))
			.TextBoxText(UUtilityFunctionLibrary::ToSI(CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType), SigFigs, !bPercentage))
			.TextBoxTooltip(FloatToFText(CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType), !bPercentage))
			.OnTextCommitted(StatOnTextCommitted(DetailBuilder, TargetStat, StatValueType, bPercentage))
			.IsPercentage(bPercentage)
			.MaxText(UUtilityFunctionLibrary::ToSI(MaxStatValue, SigFigs, !bPercentage))
			.MaxTooltip(FloatToFText(MaxStatValue, !bPercentage))
			.BarColor(CombatStatsComponent->GetStat(TargetStat).Color())
			.BarFraction(GetFraction(CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType), OverallMaxValue))
			.BarTooltip(CombatStatsComponent->GetStat(TargetStat).SupportingText().Description)
		).OverrideResetToDefault(
			FResetToDefaultOverride::Create( 
				TAttribute<bool>::CreateLambda([this, TargetStat, StatValueType, MaxStatValue]() 
				{
					switch(StatValueType)
					{
					case EStatValueType::Current:
						return FMathf::Abs(CombatStatsComponent->GetStat(TargetStat).GetValue(StatValueType) - MaxStatValue) > FMathf::Epsilon;
					default:
						return true;
					}
				}), 
				ResetClicked
			)
		)
	;
}

FSimpleDelegate CombatStatsComponentDrawer::CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder, const EStatEnum TargetStat,
	const EStatValueType StatValueType, const float MaxStatValue) const
{
	
	// Set up "on reset" button delegate
	FSimpleDelegate ResetClicked;
	switch(StatValueType)
	{
	case EStatValueType::BaseStat:
		ResetClicked = FSimpleDelegate::CreateLambda(
			[this, &DetailBuilder, &TargetStat]() 
			{
				CombatStatsComponent->RandomizeBaseStat(TargetStat);
				CombatStatsComponent->RecalculateStats();
				SaveAndRefresh(DetailBuilder);
			}
		);
		break;
	case EStatValueType::BasePairs:
		ResetClicked = FSimpleDelegate::CreateLambda(
			[this, &DetailBuilder, &TargetStat]() 
			{
				CombatStatsComponent->RandomizeBasePair(TargetStat);
				CombatStatsComponent->RecalculateStats();
				SaveAndRefresh(DetailBuilder);
			}
		);
		break;
	default:
		ResetClicked = FSimpleDelegate::CreateLambda(
			[this, &DetailBuilder, TargetStat, MaxStatValue, StatValueType]() 
			{
				CombatStatsComponent->ModifyStat(TargetStat, MaxStatValue, StatValueType, EModificationMode::SetDirectly);
				SaveAndRefresh(DetailBuilder);
			}
		) ;
	}

	return ResetClicked;
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
