#define LOCTEXT_NAMESPACE "StatsComponentDrawer"

#include "StatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"

#define STAT_SLOT() \
	+SCanvas::Slot()

#define STAT_BACKGROUND() \
	STAT_SLOT() [ \
		SNew(SColorBlock) \
		.Color(FLinearColor::Black) \
		.Size(FVector2D{MaxWidth, MaxHeight}) \
	]

#define STAT_SIMPLETEXT(StringText, BGColor) \
	SNew(STextBlock) \
		.Text(FText::FromString(StringText)) \
		.Justification(ETextJustify::Center) \
		.ColorAndOpacity(BGColor) 

#define STAT_TEXTBLOCK(StringText, BGColor) \
	STAT_SLOT() [ \
		STAT_SIMPLETEXT(StringText, BGColor) \
	] \
	.Size(FVector2D{MaxWidth, MaxHeight})
	
#define STAT_BAR(StatPointer, ValueMember, ValueMax) \
	STAT_SLOT() [ \
		SNew(SColorBlock) \
			.Color(StatPointer.Color()) \
			.Size(FVector2D{MaxWidth * StatPointer.ValueMember / ValueMax, MaxHeight}) \
			.Clipping(EWidgetClipping::ClipToBounds) \
	] \
		.HAlign(HAlign_Left) \
		.Size(FVector2D{MaxWidth - 2*Padding, MaxHeight - 2*Padding}) \
		.Position(FVector2D{Padding, Padding}) \
	STAT_SLOT()[ \
		STAT_SIMPLETEXT(StatsComponent->Health.Name(), FLinearColor::White) \
	] 

#define CURRENT_STAT_PROPERTY(TargetStat, ValueMember, ValueMax) \
	TSharedPtr<IPropertyHandle> Handle##TargetStat = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UStatsComponent, TargetStat)); \
	IDetailPropertyRow* Row##TargetStat = DetailBuilder.EditDefaultProperty(Handle##TargetStat); \
	Row##TargetStat->CustomWidget() \
		.NameContent()[ \
			SNew(SCanvas) \
				STAT_SLOT()[ \
					SNew(STextBlock) \
						.Text(FText::FromString(StatsComponent->TargetStat.Abbreviation())) \
				] \
				.Size(FVector2D{MaxWidth, MaxHeight}) \
				STAT_SLOT()[ \
					SNew(SEditableTextBox) \
						.Text(FText::FromString(FString::SanitizeFloat(StatsComponent->TargetStat.ValueMember))) \
				] \
				.Size(FVector2D{MaxWidth, MaxHeight}) \
				.HAlign(HAlign_Right) \
		] \
		.ValueContent()[ \
			SNew(SCanvas) \
				STAT_BACKGROUND() \
				STAT_BAR(StatsComponent->TargetStat, ValueMember, ValueMax) \
			];

TSharedRef<IDetailCustomization> StatsComponentDrawer::MakeInstance()
{
	return MakeShareable(new StatsComponentDrawer);
}

void StatsComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	UStatsComponent* StatsComponent = GetStatsComponent(DetailBuilder);
	SNew(SCanvas) \
					STAT_SLOT()[ \
						SNew(STextBlock) \
							.Text(FText::FromString(StatsComponent->Health.Abbreviation())) \
					].Size(FVector2D{MaxWidth, MaxHeight}) \
	;
	// Get useful limits
	float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);
	
	// Define macro (if not for GET_MEMBER_NAME_CHECKED, you could do this as a function
	SNew(SCanvas)
	+SCanvas::Slot()[
		SNew(SColorBlock) 
			.Color(StatsComponent->Health.Color()) 
			.Size(FVector2D{10, 10}) 
			.Clipping(EWidgetClipping::ClipToBounds)
			
	]
	.Size(FVector2D{MaxWidth - 2*Padding, MaxHeight - 2*Padding}) 
	.Position(FVector2D{Padding, Padding})
	+SCanvas::Slot()[
				STAT_SIMPLETEXT(StatsComponent->Health.Name(), FLinearColor::White)
			] 
	;

	CURRENT_STAT_PROPERTY(Health, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(PhysicalAttack, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(PhysicalDefense, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(SpecialAttack, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(SpecialDefense, GetCurrentValue(), MaxStatValue)
	CURRENT_STAT_PROPERTY(Haste, GetCurrentValue(), MaxPercentValue)
	CURRENT_STAT_PROPERTY(CriticalHit, GetCurrentValue(), MaxPercentValue)
				
				

	
	// Modify category slate-style
	FString CategoryName = UTF8_TO_TCHAR(CATEGORY_NAME);
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);

	// Visuals slate-style
	Category.AddCustomRow(LOCTEXT("Keyword", "Stats"))
		.NameContent()[
			SNew(STextBlock)
				.Text(FText::FromString("OK"))
			]
		.ValueContent()[
			SNew(SButton)
				.Text(FText::FromString("KOOOOO"))
			];
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
	UStatsComponent* StatsComponent = Cast<UStatsComponent>(Object.Get());

	// Guard again
	if (!StatsComponent) return nullptr;

	// Return
	return StatsComponent;
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