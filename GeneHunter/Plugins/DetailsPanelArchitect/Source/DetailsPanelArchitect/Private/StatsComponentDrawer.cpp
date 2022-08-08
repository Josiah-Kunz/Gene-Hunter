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
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(LevelCategoryName),
		FText::FromString(LevelCategoryName),
		ECategoryPriority::Important);
	Category.AddCustomRow(LOCTEXT("Keyword", "Level"))

		// Name
		.NameContent()[
			SNew(SCanvas)

				// Text
				+SCanvas::Slot()[
					SNew(STextBlock)
						.Text(FText::FromString("Lv."))
						.ToolTipText( FText::FromString("Level"))
				]
				.Size(FVector2D{StatAbbrevMaxWidth, MaxHeight})
				.Position(FVector2D{0, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)

				// Current (EditableText)
				+SCanvas::Slot()[
					SNew(SEditableTextBox)
						.Text(FText::FromString(FString::FromInt(StatsComponent->GetLevel())))
						.OnTextCommitted_Lambda(
								[this, &DetailBuilder](const FText& InText, ETextCommit::Type InTextCommit)
								{
									StatsComponent->SetLevel(UUtilityFunctionLibrary::FromSI(InText));
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
						.Text(FText::FromString(FString::FromInt(StatsComponent->MaxLevel())))
				]
				.Size(FVector2D{StatInputWidth, MaxHeight})
				.Position(FVector2D{StatAbbrevMaxWidth + StatInputWidth + SlashWidth, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
		]

		// Level bar
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
						.Color(FLinearColor::Green)
						.Clipping(EWidgetClipping::ClipToBounds)
						.ToolTipText(FText::FromString(FString::Printf(TEXT(
							"The higher the level, the stronger the stats! The max level is %s."),
							*FString::FromInt(StatsComponent->MaxLevel()
						))))
				]
				.Position(FVector2D{Padding, 0})
				.Size(FVector2D{(ValueMaxWidth - 2*Padding) * StatsComponent->GetLevel()/StatsComponent->MaxLevel(), MaxHeight - 2*Padding})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
	];
}

void StatsComponentDrawer::CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	BarWidgetFromNew(
			DetailBuilder, "Level",
		FTextWidgetParameters{
			FText::FromString("Exp"),
			FText::FromString("Cumulative experience points"),
			FVector2D{StatAbbrevMaxWidth, MaxHeight}
		},
		FEditableTextBoxWidgetParameters{
			{
				UUtilityFunctionLibrary::ToSI(StatsComponent->GetCumulativeExp(), SigFigs),
				FText::GetEmpty(),
				FVector2D{StatInputWidth, MaxHeight},
				FVector2D{StatAbbrevMaxWidth, 0}
			}
		},
		FTextWidgetParameters{
			UUtilityFunctionLibrary::ToSI(StatsComponent->GetMaxExp(), SigFigs),
			FText::GetEmpty(),
			FVector2D{StatInputWidth, MaxHeight},
			FVector2D{StatAbbrevMaxWidth + StatInputWidth + SlashWidth, 0}
		},
		FBarWidgetParameters{
			{
				FText::GetEmpty(),
				FText::FromString("Change in exp = change in level"),
				FVector2D{ValueMaxWidth, MaxHeight}
			},
			FLinearColor::Black,
			FLinearColor{0.7f, 0, 0.7f},
			StatsComponent->GetCumulativeExp()/StatsComponent->GetMaxExp()
		},
		[this, &DetailBuilder](const FText& InText, ETextCommit::Type InTextCommit)
								{
									StatsComponent->SetCumulativeExp(UUtilityFunctionLibrary::FromSI(InText));
									DetailBuilder.ForceRefreshDetails();
								}
	);
	
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(LevelCategoryName),
		FText::FromString(LevelCategoryName),
		ECategoryPriority::Important);
	Category.AddCustomRow(LOCTEXT("Keyword", "Level"))

		// Name
		.NameContent()[
			SNew(SCanvas)

				// Text
				+SCanvas::Slot()[
					SNew(STextBlock)
						.Text(FText::FromString("Exp."))
						.ToolTipText( FText::FromString("(Non-cumulative) experience points"))
				]
				.Size(FVector2D{StatAbbrevMaxWidth, MaxHeight})
				.Position(FVector2D{0, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)

				// Current (EditableText)
				+SCanvas::Slot()[
					SNew(SEditableTextBox)
						.Text(FText::FromString(FString::FromInt(StatsComponent->GetLevel())))
						.OnTextCommitted_Lambda(
								[this, &DetailBuilder](const FText& InText, ETextCommit::Type InTextCommit)
								{
									StatsComponent->SetLevel(UUtilityFunctionLibrary::FromSI(InText));
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
						.Text(FText::FromString(FString::FromInt(StatsComponent->MaxLevel())))
				]
				.Size(FVector2D{StatInputWidth, MaxHeight})
				.Position(FVector2D{StatAbbrevMaxWidth + StatInputWidth + SlashWidth, 0})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
		]

		// Level bar
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
						.Color(FLinearColor::Green)
						.Clipping(EWidgetClipping::ClipToBounds)
						.ToolTipText(FText::FromString(FString::Printf(TEXT(
							"The higher the level, the stronger the stats! The max level is %s."),
							*FString::FromInt(StatsComponent->MaxLevel()
						))))
				]
				.Position(FVector2D{Padding, 0})
				.Size(FVector2D{(ValueMaxWidth - 2*Padding) * StatsComponent->GetLevel()/StatsComponent->MaxLevel(), MaxHeight - 2*Padding})
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
	];
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
							[&TargetStat, StatValueType, &DetailBuilder](const FText& InText, ETextCommit::Type InTextCommit)
								{
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

template <typename F>
void StatsComponentDrawer::BarWidgetFromNew(IDetailLayoutBuilder& DetailBuilder, const FString CategoryName,
	FTextWidgetParameters LabelWidgetParameters, FEditableTextBoxWidgetParameters EditableTextBoxWidgetParameters,
	FTextWidgetParameters MaxWidgetParameters, FBarWidgetParameters BarWidgetParameters, F&& OnTextCommitted_Lambda)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);
	Category.AddCustomRow(LOCTEXT("Keyword", "BarWidget")).WholeRowContent()[
		SNew(SCanvas)

			// Text
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(LabelWidgetParameters.Text)
					.ToolTipText(LabelWidgetParameters.Tooltip)
			]
			.Size(LabelWidgetParameters.WidgetSize)
			.Position(LabelWidgetParameters.WidgetPosition)
			.HAlign(LabelWidgetParameters.WidgetHAlign)
			.VAlign(LabelWidgetParameters.WidgetVAlign)

			// Current (EditableText)
			+SCanvas::Slot()[
				SNew(SEditableTextBox)
					.Text(EditableTextBoxWidgetParameters.Text)
					.ToolTip(EditableTextBoxWidgetParameters.Tooltip)
					.OnTextCommitted_Lambda(OnTextCommitted_Lambda)
			] 
			.Size(EditableTextBoxWidgetParameters.WidgetSize)
			.Position(EditableTextBoxWidgetParameters.WidgetPosition)
			.HAlign(EditableTextBoxWidgetParameters.WidgetHAlign)
			.VAlign(EditableTextBoxWidgetParameters.WidgetVAlign)

			// Slash
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(FText::FromString("/"))
			]
			.Size(FVector2D{SlashWidth, EditableTextBoxWidgetParameters.WidgetSize.Y})
			.Position(FVector2D{EditableTextBoxWidgetParameters.WidgetPosition.X + EditableTextBoxWidgetParameters.WidgetSize.X, 0})
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)

			// Max
			+SCanvas::Slot()[
				SNew(STextBlock)
					.Text(MaxWidgetParameters.Text)
					.ToolTip(MaxWidgetParameters.Tooltip)
			]
			.Size(MaxWidgetParameters.WidgetSize)
			.Position(MaxWidgetParameters.WidgetPosition)
			.HAlign(MaxWidgetParameters.WidgetHAlign)
			.VAlign(MaxWidgetParameters.WidgetVAlign)

			// Background
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(BarWidgetParameters.BackgroundColor)
			]
			.Position(BarWidgetParameters.WidgetPosition)
			.Size(BarWidgetParameters.WidgetSize)
			.HAlign(BarWidgetParameters.WidgetHAlign)
			.VAlign(BarWidgetParameters.WidgetVAlign)

			// Stat bar
			+SCanvas::Slot()[
				SNew(SColorBlock) 
					.Color(BarWidgetParameters.BarColor)
					.Clipping(EWidgetClipping::ClipToBounds)
					.ToolTipText(BarWidgetParameters.Tooltip)
			]
			.Position(BarWidgetParameters.WidgetPosition)
			.Size(FVector2D{
				BarWidgetParameters.BarFraction * BarWidgetParameters.WidgetSize.X - 2*BarWidgetParameters.Padding,
				BarWidgetParameters.WidgetSize.Y - 2*BarWidgetParameters.Padding
			})
			.HAlign(BarWidgetParameters.WidgetHAlign)
			.VAlign(BarWidgetParameters.WidgetVAlign)
	];
		
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