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

	BarWidgetFromNew(
			DetailBuilder, "Level", FEditableBarWidgetParameters{

				// Label
				FText::FromString("Lv."),
				FText::FromString("Level"),

				// EditableText
				FText::FromString(FString::FromInt(StatsComponent->GetLevel())),
				[this, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
					{
						const int NewLevel = UUtilityFunctionLibrary::FromSI(InText);
						if (NewLevel == StatsComponent->GetLevel())
							return;
						if (UserCommitted(InTextCommit))
							StatsComponent->SetLevel(NewLevel);
						DetailBuilder.ForceRefreshDetails();
					},

				// Max
				FText::FromString(FString::FromInt(StatsComponent->MaxLevel())),
				FText::FromString(FString::Printf(TEXT("The max level can be changed in-script via inheritance (for, e.g., bosses)."))),

				// Bar
				FLinearColor::Green,
				(1.0f * StatsComponent->GetLevel())/StatsComponent->MaxLevel(),
				FText::FromString(
					FString::Printf(TEXT(
					"The higher the level, the stronger the stats! The max level is %s."),
					*FString::FromInt(StatsComponent->MaxLevel())
					)
				),

				// Reset button
				true,
				{[this, &DetailBuilder]()
					{
						StatsComponent->SetLevel(1);
						DetailBuilder.ForceRefreshDetails();
					},
				},
			}
		);
}

void StatsComponentDrawer::CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Exp to level
	BarWidgetFromNew(
			DetailBuilder, "Level", FEditableBarWidgetParameters{

				// Label
				FText::FromString("Exp"),
				FText::FromString("Experience points within the level (non-cumulative experience points)"),

				// EditableTextBox
				UUtilityFunctionLibrary::ToSI(StatsComponent->GetExp(), SigFigs),
				[this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
					{

						// Check if anything happened
						const int DiffXP = UUtilityFunctionLibrary::FromSI(InText) - StatsComponent->GetExp();
						if (DiffXP == 0)
							return;

						// Check to see if anything changed (avoids rounding errors)
						if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetExp(), SigFigs)))
							return;

						// Use did something
						if (UserCommitted(CommitType))
							StatsComponent->AddCumulativeExp(DiffXP);

						// Refresh either way
						DetailBuilder.ForceRefreshDetails();
					},

				// Max
				UUtilityFunctionLibrary::ToSI(StatsComponent->GetTotalExpThisLevel(), SigFigs),
				FText::GetEmpty(),

				// Bar
				FLinearColor{0.9f, 0, 0.9f},
				StatsComponent->GetExp()/StatsComponent->GetTotalExpThisLevel(),
				FText::FromString("Change in exp = change in level"),

				// Reset button
				true,
				{[this, &DetailBuilder]()
					{
						StatsComponent->SetCumulativeExp(StatsComponent->GetCumulativeExpFromLevel(StatsComponent->GetLevel()));
						DetailBuilder.ForceRefreshDetails();
					},
				},
			}
		);
	
	// Cumulative
	BarWidgetFromNew(
		DetailBuilder, "Level", FEditableBarWidgetParameters{

			// Label
			FText::FromString("CXP"),
			FText::FromString("Cumulative experience points"),
			
			// EditableTextBox
			UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs),
			[this, &DetailBuilder](const FText& InText, const ETextCommit::Type CommitType)
				{

					// Check to see if anything changed (avoids rounding errors)
					if (InText.EqualTo(UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs)))
						return;

					// Change depending on commit type (might have hit "esc", so no changes)
					if (UserCommitted(CommitType))
						StatsComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));

					// Refresh either way
					DetailBuilder.ForceRefreshDetails();
				},

			// Max
			UUtilityFunctionLibrary::ToSI(StatsComponent->GetMaxExp(), SigFigs),
			FText::GetEmpty(),

			// Bar
			FLinearColor{0.7f, 0, 0.7f},
			StatsComponent->GetCumulativeExp()/StatsComponent->GetMaxExp(),
			FText::FromString("Change in exp = change in level"),
				
			// Reset button
			true,
			{[this, &DetailBuilder]()
				{
					StatsComponent->SetCumulativeExp(0);
					DetailBuilder.ForceRefreshDetails();
				},
			},
		}
	);
}


void StatsComponentDrawer::CustomizeStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	const float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);
	
	CURRENT_STAT_PROPERTY(Health, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(PhysicalAttack, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(PhysicalDefense, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(SpecialAttack, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(SpecialDefense, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(Haste, GetCurrentValue(), MaxPercentValue)
	CURRENT_STAT_PROPERTY(CriticalHit, GetCurrentValue(), MaxPercentValue)
	
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
					.Text(Params.LabelText)
					.ToolTipText(Params.LabelTooltip)
			]
			.Size(Params.LabelSize)
			.Position(Params.LabelPosition)
			.HAlign(Params.LabelHAlign)
			.VAlign(Params.LabelVAlign)

			// Current (EditableText)
			+SCanvas::Slot()[
				SNew(SEditableTextBox)
					.Text(Params.EditableTextBoxText)
					.ToolTipText(Params.EditableTextBoxTooltip)
					.OnTextCommitted_Lambda(Params.OnTextCommitted)
			] 
			.Size(Params.EditableTextBoxSize)
			.Position(Params.EditableTextBoxPosition)
			.HAlign(Params.EditableTextBoxHAlign)
			.VAlign(Params.EditableTextBoxVAlign)

			// Slash
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(Params.SlashText)
			]
			.Size(Params.SlashSize)
			.Position(Params.SlashPosition)
			.HAlign(Params.SlashHAlign)
			.VAlign(Params.SlashVAlign)

			// Max
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(Params.MaxText)
					.ToolTipText(Params.MaxTooltip)
			]
			.Size(Params.MaxSize)
			.Position(Params.MaxPosition)
			.HAlign(Params.MaxHAlign)
			.VAlign(Params.MaxVAlign)

			// Background
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(Params.BarBackgroundColor)
			]
			.Position(Params.BarPosition)
			.Size(Params.BarSize)
			.HAlign(Params.BarHAlign)
			.VAlign(Params.BarVAlign)

			// Stat bar
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(Params.BarColor)
					.Clipping(EWidgetClipping::ClipToBounds)
					.ToolTipText(Params.BarTooltip)
			]
			.Position(FVector2D{
				Params.BarPosition.X + Params.BarPadding,
				Params.BarPosition.Y
				})
			.Size(FVector2D{
				Params.BarFraction * Params.BarSize.X - 2*Params.BarPadding,
				Params.BarSize.Y - 2*Params.BarPadding
			})
			.HAlign(Params.BarHAlign)
			.VAlign(Params.BarVAlign)
	)
	.OverrideResetToDefault(
		FResetToDefaultOverride::Create( 
			TAttribute<bool>::CreateLambda([Params]() 
			{ 
				return Params.bShowReset; 
			}), 
			FSimpleDelegate::CreateLambda([Params]() 
			{ 
				Params.OnReset();
			}) 
		)
	)
	;
	Widget.HAlign(HAlign_Left);
	Widget.VAlign(VAlign_Center);
}


void StatsComponentDrawer::StatWidget(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> PropertyHandle,
	FStat& TargetStat, const EStatValueType StatValueType, const float MaxValue)
{

	// Content
	BarWidgetFromExisting(DetailBuilder, PropertyHandle, FEditableBarWidgetParameters{

		// Label
		FText::FromString(TargetStat.Abbreviation()),
		FText::FromString(TargetStat.Name()),

		// EditableText
		UUtilityFunctionLibrary::ToSI(TargetStat.GetValue(StatValueType), SigFigs),
		[&TargetStat, StatValueType, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
			{
				if (UserCommitted(InTextCommit))
					TargetStat.ModifyValue( UUtilityFunctionLibrary::FromSI(InText), StatValueType, EModificationMode::SetDirectly);
				DetailBuilder.ForceRefreshDetails();
			},

		// Max
		UUtilityFunctionLibrary::ToSI(TargetStat.GetPermanentValue(), SigFigs),
		FText::FromString("Max values are calculated via functions in the script and are permanent. If you'd like to calculate them differently, create your own C++ class."),

		// Bar
		TargetStat.Color(),
		TargetStat.GetValue(StatValueType) / MaxValue,
		TargetStat.SupportingText().Description,

		// Reset button
			true,
			{[this, &DetailBuilder, &TargetStat]()
				{
					TargetStat.SetCurrentValue(TargetStat.GetPermanentValue());
					DetailBuilder.ForceRefreshDetails();
				},
			},
	});
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