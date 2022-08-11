#define LOCTEXT_NAMESPACE "StatsComponentDrawer"

#include "StatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"

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
	CustomizeStatsDetails(DetailBuilder);
	
}

void StatsComponentDrawer::CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder)
{

	FEditableBarWidgetParameters Params = {};

	// Label
	Params.Label.Text = FText::FromString("Lv.");
	Params.Label.Tooltip = FText::FromString("Level");

	// EditableText
	Params.TextBox.Text = FText::FromString(FString::FromInt(StatsComponent->GetLevel()));
	Params.TextBox.Tooltip = FText::FromString(FString::Printf(TEXT("%i"), StatsComponent->GetLevel()));
	Params.TextBox.OnTextCommitted = [this, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
	{
		const int NewLevel = UUtilityFunctionLibrary::FromSI(InText);
		if (NewLevel == StatsComponent->GetLevel())
			return;
		if (UserCommitted(InTextCommit))
			StatsComponent->SetLevel(NewLevel);
		DetailBuilder.ForceRefreshDetails();
	},

	// Max
	Params.Max.Text = FText::FromString(FString::FromInt(StatsComponent->MaxLevel()));
	Params.Max.Tooltip = FText::FromString(FString::FromInt(StatsComponent->MaxLevel()));

	// Bar
	Params.Bar.BarColor = FLinearColor::Green;
	Params.Bar.BarFraction = (1.0f * StatsComponent->GetLevel())/StatsComponent->MaxLevel();
	Params.Bar.Tooltip = FText::FromString(
					FString::Printf(TEXT(
					"The higher the level, the stronger the stats! The max level is %s."),
					*FString::FromInt(StatsComponent->MaxLevel())
					)
				);

	// Reset
	Params.Reset.bShowReset = true;
	Params.Reset.OnReset = [this, &DetailBuilder]()
		{
			StatsComponent->SetLevel(1);
			DetailBuilder.ForceRefreshDetails();
		};
	Params.Reset.Tooltip = FText::FromString(FString::Printf(
		TEXT("Resets the current level (%i) to the minimum (1)."),
		StatsComponent->GetLevel()
		));

	BarWidgetFromNew(DetailBuilder, "Level", Params);
}

void StatsComponentDrawer::CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder)
{

	FEditableBarWidgetParameters ExpParams = {};

	// Label
	ExpParams.Label.Text = FText::FromString("Exp");
	ExpParams.Label.Tooltip = FText::FromString("Experience points within the level (non-cumulative experience points)");
	
	// EditableTextBox
	ExpParams.TextBox.Text = UUtilityFunctionLibrary::ToSI(StatsComponent->GetExp(), SigFigs, true);
	ExpParams.TextBox.OnTextCommitted = [this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
		{

			// Check if anything happened
			const int DiffXP = UUtilityFunctionLibrary::FromSI(InText) - StatsComponent->GetExp();
			if (DiffXP == 0)
				return;

			// Check to see if anything changed (avoids rounding errors)
			if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetExp(), SigFigs, true)))
				return;

			// Use did something
			if (UserCommitted(CommitType))
				StatsComponent->AddCumulativeExp(DiffXP);

			// Refresh either way
			DetailBuilder.ForceRefreshDetails();
		};
	ExpParams.TextBox.Tooltip = FText::FromString(FString::Printf(
		TEXT("%s"),
		*FloatToFText(StatsComponent->GetExp(), true).ToString()
		));

	// Max
	ExpParams.Max.Text = UUtilityFunctionLibrary::ToSI(StatsComponent->GetTotalExpThisLevel(), SigFigs, true);
	ExpParams.Max.Tooltip = FText::FromString(FString::Printf(
		TEXT("%s"),
		*FloatToFText(StatsComponent->GetTotalExpThisLevel(), true).ToString()
		));

	// Bar
	ExpParams.Bar.BarColor = FLinearColor{0.9f, 0.1f, 0.9f};
	ExpParams.Bar.BarFraction = StatsComponent->GetExp()/StatsComponent->GetTotalExpThisLevel();
	ExpParams.Bar.Tooltip = FText::FromString("Change in exp = change in level");

	// Reset
	ExpParams.Reset.bShowReset = true;
	ExpParams.Reset.OnReset = [this, &DetailBuilder]()
		{
			StatsComponent->SetCumulativeExp(StatsComponent->GetCumulativeExpFromLevel(StatsComponent->GetLevel()));
			DetailBuilder.ForceRefreshDetails();
		};
	ExpParams.Reset.Tooltip = FText::FromString("Resets the (non-cumulative) exp for this level to 0.");
	
	// Exp to level
	BarWidgetFromNew(DetailBuilder, "Level", ExpParams);
	
	// Cumulative
	FEditableBarWidgetParameters CxpParams = {};

	// Label
	CxpParams.Label.Text = FText::FromString("CXP");
	CxpParams.Label.Tooltip = FText::FromString("Cumulative experience points");

	// EditableTextBox
	CxpParams.TextBox.Text = UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs, true);
	CxpParams.TextBox.Tooltip = FText::FromString(FString::Printf(
		TEXT("%s"),
		*FloatToFText(StatsComponent->GetCumulativeExp(), true).ToString()
		));
	CxpParams.TextBox.OnTextCommitted = [this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
		{

			// Check to see if anything changed (avoids rounding errors)
			if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs, true)))
				return;

			// Change depending on commit type (might have hit "esc", so no changes)
			if (UserCommitted(CommitType))
				StatsComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));

			// Refresh either way
			DetailBuilder.ForceRefreshDetails();
		};

	// Max
	CxpParams.Max.Text = UUtilityFunctionLibrary::ToSI(StatsComponent->GetMaxExp(), SigFigs, true);
	CxpParams.Max.Tooltip = FText::FromString(FString::Printf(
		TEXT("Max cumulative exp at level %i is %s."),
		StatsComponent->MaxLevel(),
		*FloatToFText(StatsComponent->GetMaxExp(), true).ToString()
		));

	// Bar
	CxpParams.Bar.BarColor = FLinearColor{0.5f, 0, 0.5f};
	CxpParams.Bar.BarFraction = StatsComponent->GetCumulativeExp()/StatsComponent->GetMaxExp();
	CxpParams.Bar.Tooltip = FText::FromString("Change in exp = change in level"); 

	// Reset
	CxpParams.Reset.bShowReset = true;
	CxpParams.Reset.OnReset = [this, &DetailBuilder]()
		{
			StatsComponent->SetCumulativeExp(0);
			DetailBuilder.ForceRefreshDetails();
		};
	CxpParams.Reset.Tooltip = FText::FromString("Resets the cumulative exp to its minimum (1; level 1).");
	
	BarWidgetFromNew(DetailBuilder, "Level", CxpParams);
}


void StatsComponentDrawer::CustomizeStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	const float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);
	
	CURRENT_STAT_PROPERTY(Health, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(PhysicalDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialAttack, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(SpecialDefense, GetCurrentValue(), MaxStatValue, false)
	CURRENT_STAT_PROPERTY(Haste, GetCurrentValue(), MaxPercentValue, true)
	CURRENT_STAT_PROPERTY(CriticalHit, GetCurrentValue(), MaxPercentValue, true)
	
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

void StatsComponentDrawer::BarWidgetFromNew(IDetailLayoutBuilder& DetailBuilder, const FString CategoryName,
                                            FEditableBarWidgetParameters Params)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);


	BarWidgetBase(
		Category
			.AddCustomRow(LOCTEXT("Keyword", "BarWidget"))
			.WholeRowContent()
		, Params);
}

void StatsComponentDrawer::BarWidgetFromExisting(IDetailLayoutBuilder& DetailBuilder,
	TSharedPtr<IPropertyHandle> PropertyHandle, FEditableBarWidgetParameters Params)
{
	IDetailPropertyRow* Row = DetailBuilder.EditDefaultProperty(PropertyHandle);
	BarWidgetBase(Row->CustomWidget().WholeRowContent(), Params);
}

void StatsComponentDrawer::BarWidgetBase(FDetailWidgetDecl& Widget, FEditableBarWidgetParameters Params)
{
	Widget.operator[](
		SNew(SCanvas)

			// Text
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(Params.Label.Text)
					.ToolTipText(Params.Label.Tooltip)
			]
			.Size(Params.Label.WidgetSize)
			.Position(Params.Label.WidgetPosition)
			.HAlign(Params.Label.WidgetHAlign)
			.VAlign(Params.Label.WidgetVAlign)

			// Current (EditableText)
			+SCanvas::Slot()[
				SNew(SEditableTextBox)
					.Text(Params.TextBox.Text)
					.ToolTipText(Params.TextBox.Tooltip)
					.OnTextCommitted_Lambda(Params.TextBox.OnTextCommitted)
			] 
			.Size(Params.TextBox.WidgetSize)
			.Position(Params.TextBox.WidgetPosition)
			.HAlign(Params.TextBox.WidgetHAlign)
			.VAlign(Params.TextBox.WidgetVAlign)

			// Slash
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(Params.Slash.Text)
			]
			.Size(Params.Slash.WidgetSize)
			.Position(Params.Slash.WidgetPosition)
			.HAlign(Params.Slash.WidgetHAlign)
			.VAlign(Params.Slash.WidgetVAlign)

			// Max
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(Params.Max.Text)
					.ToolTipText(Params.Max.Tooltip)
			]
			.Size(Params.Max.WidgetSize)
			.Position(Params.Max.WidgetPosition)
			.HAlign(Params.Max.WidgetHAlign)
			.VAlign(Params.Max.WidgetVAlign)

			// Outline
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(Params.Bar.OutlineColor)
					.ToolTipText(Params.Bar.Tooltip)
					.CornerRadius(Params.Bar.CornerRadius)
			]
			.Position(Params.Bar.WidgetPosition)
			.Size(Params.Bar.WidgetSize)
			.HAlign(Params.Bar.WidgetHAlign)
			.VAlign(Params.Bar.WidgetVAlign)
			
			// Background
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(Params.Bar.BackgroundColor)
					.ToolTipText(Params.Bar.Tooltip)
					.CornerRadius(Params.Bar.CornerRadius)
			]
			.Position(FVector2D{
				Params.Bar.WidgetPosition.X + Params.Bar.Padding,
				Params.Bar.WidgetPosition.Y
				})
			.Size(FVector2D{
				Params.Bar.WidgetSize.X - 2*Params.Bar.Padding,
				Params.Bar.WidgetSize.Y - 2*Params.Bar.Padding
				})
			.HAlign(Params.Bar.WidgetHAlign)
			.VAlign(Params.Bar.WidgetVAlign)

			// Stat bar
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(Params.Bar.BarColor)
					.Clipping(EWidgetClipping::ClipToBounds)
					.ToolTipText(Params.Bar.Tooltip)
					.CornerRadius(Params.Bar.CornerRadius)
			]
			.Position(FVector2D{
				Params.Bar.WidgetPosition.X + Params.Bar.Padding,
				Params.Bar.WidgetPosition.Y
				})
			.Size(FVector2D{
				Params.Bar.BarFraction * Params.Bar.WidgetSize.X - 2*Params.Bar.Padding,
				Params.Bar.WidgetSize.Y - 2*Params.Bar.Padding
			})
			.HAlign(Params.Bar.WidgetHAlign)
			.VAlign(Params.Bar.WidgetVAlign)
	)
	.OverrideResetToDefault(
		FResetToDefaultOverride::Create( 
			TAttribute<bool>::CreateLambda([Params]() 
			{ 
				return Params.Reset.bShowReset; 
			}), 
			FSimpleDelegate::CreateLambda([Params]() 
			{ 
				Params.Reset.OnReset();
			}) 
		)
	)
	;
	Widget.HAlign(HAlign_Left);
	Widget.VAlign(VAlign_Center);
	
}


void StatsComponentDrawer::StatWidget(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> PropertyHandle,
	FStat& TargetStat, const EStatValueType StatValueType, const float MaxValue, const bool bPercentage)
{

	// Parameters
	FEditableBarWidgetParameters Params = {};

	// Label
	Params.Label.Text = FText::FromString(TargetStat.Abbreviation());
	Params.Label.Tooltip = FText::FromString(TargetStat.Name());

	// EditableTextBox
	Params.TextBox.Text = UUtilityFunctionLibrary::ToSI(TargetStat.GetValue(StatValueType), SigFigs, !bPercentage);
	Params.TextBox.Tooltip = FloatToFText(TargetStat.GetCurrentValue(), !bPercentage);
	Params.TextBox.OnTextCommitted = [&TargetStat, StatValueType, &DetailBuilder, bPercentage](const FText& InText, const ETextCommit::Type InTextCommit)
		{
			// Check to see if anything changed (avoids rounding errors)
			if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(TargetStat.GetCurrentValue(), SigFigs, !bPercentage)))
				return;

			// Check commit method
			if (UserCommitted(InTextCommit))
				TargetStat.ModifyValue( UUtilityFunctionLibrary::FromSI(InText), StatValueType, EModificationMode::SetDirectly);

			// Refresh regardless
			DetailBuilder.ForceRefreshDetails();
		};
	if (bPercentage)
		Params.TextBox.WidgetSize = FVector2D{
			Params.TextBox.WidgetSize.X - Params.Slash.WidgetSize.X,
			Params.TextBox.WidgetSize.Y
		};

	// Slash is preceded by percent?
	if (bPercentage)
	{
		Params.Slash.Text = FText::FromString(FString::Printf(
			TEXT("%% %s"),
			*Params.Slash.Text.ToString()
			));
		Params.Slash.WidgetPosition = FVector2D{
			Params.Slash.WidgetPosition.X - Params.Slash.WidgetSize.X,
			Params.Slash.WidgetPosition.Y
		};
		Params.Slash.WidgetSize = FVector2D{
			Params.Slash.WidgetSize.X + Params.Slash.WidgetSize.X,
			Params.Slash.WidgetSize.Y
		};
	}

	// Max
	Params.Max.Text = UUtilityFunctionLibrary::ToSI(TargetStat.GetPermanentValue(), SigFigs, !bPercentage);
	Params.Max.Tooltip = FloatToFText(TargetStat.GetPermanentValue(), !bPercentage);
	if (bPercentage)
		Params.Max.Text = FText::FromString(FString::Printf(
				TEXT("%s%%"),
				*Params.Max.Text.ToString()
			));
	
	// Bar
	Params.Bar.BarColor = TargetStat.Color();
	Params.Bar.BarFraction = TargetStat.GetValue(StatValueType) / MaxValue;
	Params.Bar.Tooltip = TargetStat.SupportingText().Description;

	// Reset
	Params.Reset.bShowReset = true;
	Params.Reset.OnReset = [this, &DetailBuilder, &TargetStat]()
		{
			TargetStat.SetCurrentValue(TargetStat.GetPermanentValue());
			DetailBuilder.ForceRefreshDetails();
		};
	Params.Reset.Tooltip = FText::FromString(FString::Printf(
		TEXT("Resets the current %s (%s) to the permanent value (%s)."),
		*TargetStat.Name(),
		*FloatToFText(TargetStat.GetCurrentValue(), !bPercentage).ToString(),
		*FloatToFText(TargetStat.GetPermanentValue(), !bPercentage).ToString()
	));
	
	// Content
	BarWidgetFromExisting(DetailBuilder, PropertyHandle, Params);
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
			Max = FMathf::Max(Max, Stat->BasePairs);
			break;
		case EStatValueType::BaseStat:
			Max = FMathf::Max(Max, Stat->BaseStat);
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