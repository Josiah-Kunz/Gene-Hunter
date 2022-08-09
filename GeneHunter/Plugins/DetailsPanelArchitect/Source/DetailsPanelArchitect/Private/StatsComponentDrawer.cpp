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
						if (UserCommitted(InTextCommit))
							StatsComponent->SetLevel(UUtilityFunctionLibrary::FromSI(InText));
						DetailBuilder.ForceRefreshDetails();
					},

				// Max
				FText::FromString(FString::FromInt(StatsComponent->MaxLevel())),
				FText::FromString(FString::Printf(TEXT("The max level can be changed in-script via inheritance (for, e.g., bosses)."))),

				// Bar
				FLinearColor::Green,
				(1.0f * StatsComponent->GetLevel())/StatsComponent->MaxLevel(),
				FText::FromString(FString::Printf(TEXT(
							"The higher the level, the stronger the stats! The max level is %s."),
							*FString::FromInt(StatsComponent->MaxLevel())
							))
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

						// Use did something
						if (UserCommitted(CommitType))
						{
							const int DiffXP = UUtilityFunctionLibrary::FromSI(InText) - StatsComponent->GetExp();
							StatsComponent->AddCumulativeExp(DiffXP);
						}

						// User cancelled; revert changes
						DetailBuilder.ForceRefreshDetails();
					},

				// Max
				UUtilityFunctionLibrary::ToSI(StatsComponent->GetTotalExpThisLevel(), SigFigs),
				FText::GetEmpty(),

				// Bar
				FLinearColor{0.9f, 0, 0.9f},
				StatsComponent->GetExp()/StatsComponent->GetTotalExpThisLevel(),
				FText::FromString("Change in exp = change in level")
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
					if (UserCommitted(CommitType))
						StatsComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));
					DetailBuilder.ForceRefreshDetails();
				},

			// Max
			UUtilityFunctionLibrary::ToSI(StatsComponent->GetMaxExp(), SigFigs),
			FText::GetEmpty(),

			// Bar
			FLinearColor{0.7f, 0, 0.7f},
			StatsComponent->GetCumulativeExp()/StatsComponent->GetMaxExp(),
			FText::FromString("Change in exp = change in level")
		}
	);
}


void StatsComponentDrawer::CustomizeStatsDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get useful limits
	const float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	const float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);
	
	// Define macro (if not for GET_MEMBER_NAME_CHECKED, you could do this as a function
#define CURRENT_STAT_PROPERTY(TargetStat, ValueMember, ValueMax) \
	const TSharedPtr<IPropertyHandle> Handle##TargetStat = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UStatsComponent, TargetStat)); \
	BuildStat(DetailBuilder, Handle##TargetStat, StatsComponent->TargetStat, EStatValueType::Current, ValueMax);
	
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

void StatsComponentDrawer::BuildStat(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> PropertyHandle,
	FStat& TargetStat, const EStatValueType StatValueType, const float MaxValue)
{
	IDetailPropertyRow* Row = DetailBuilder.EditDefaultProperty(PropertyHandle);
	Row->CustomWidget()

		// "Name" content
		.NameContent()[ 
			SNew(SCanvas)

				// Abbreviation
				+SCanvas::Slot()[
					SNew(STextBlock)
						.Text(FText::FromString(TargetStat.Abbreviation()))
						.ToolTipText( FText::FromString(TargetStat.Name()))
				]
				.Size(FVector2D{StatAbbrevMaxWidth, MaxHeight})
				.Position(FVector2D{0, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)

				// Current (EditableText)
				+SCanvas::Slot()[
					SNew(SEditableTextBox)
						.Text(UUtilityFunctionLibrary::ToSI(TargetStat.GetValue(StatValueType), SigFigs))
						.OnTextCommitted_Lambda(
							[&TargetStat, StatValueType, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
								{
									if (UserCommitted(InTextCommit))
										TargetStat.ModifyValue( UUtilityFunctionLibrary::FromSI(InText), StatValueType, EModificationMode::SetDirectly);
									DetailBuilder.ForceRefreshDetails();
								}
						)
				] 
				.Size(FVector2D{StatInputWidth, MaxHeight})
				.Position(FVector2D{StatAbbrevMaxWidth, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)

				// Slash
				+SCanvas::Slot()[
					SNew(STextBlock)
						.Text(FText::FromString("/"))
				]
				.Size(FVector2D{SlashWidth, MaxHeight})
				.Position(FVector2D{StatAbbrevMaxWidth + StatInputWidth, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)

				// Max
				+SCanvas::Slot()[
					SNew(STextBlock)
						.Text(UUtilityFunctionLibrary::ToSI(TargetStat.GetPermanentValue(), SigFigs))
				]
				.Size(FVector2D{StatInputWidth, MaxHeight})
				.Position(FVector2D{StatAbbrevMaxWidth + StatInputWidth + SlashWidth, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
		]

		// "Value" content
		.ValueContent()[
			SNew(SCanvas)

				// Background
				+SCanvas::Slot()[
					SNew(SColorBlock) 
						.Color(FLinearColor::Black)
				]
				.Position(FVector2D{0, 0})
				.Size(FVector2D{ValueMaxWidth, MaxHeight})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				
				// Stat bar
				+SCanvas::Slot()[
					SNew(SColorBlock) 
						.Color(TargetStat.Color())
						.Clipping(EWidgetClipping::ClipToBounds)
						.ToolTipText(TargetStat.SupportingText().Description)
				]
				.Position(FVector2D{Padding, 0})
				.Size(FVector2D{(ValueMaxWidth - 2*Padding) * TargetStat.GetValue(StatValueType) / MaxValue, MaxHeight - 2*Padding})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
	];
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
	Category.AddCustomRow(LOCTEXT("Keyword", "BarWidget")).WholeRowContent()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
	[
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
	];
}

void StatsComponentDrawer::BarWidgetFromExisting(IDetailLayoutBuilder& DetailBuilder, const FString CategoryName,
	TSharedPtr<IPropertyHandle> PropertyHandle, FEditableBarWidgetParameters Params)
{
	IDetailPropertyRow* Row = DetailBuilder.EditDefaultProperty(PropertyHandle);
	BarWidgetBase(Row->CustomWidget().WholeRowContent());
}

void StatsComponentDrawer::BarWidgetBase(FDetailWidgetDecl& Widget)
{
	Widget.operator[](
		SNew(SCanvas)
		);
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