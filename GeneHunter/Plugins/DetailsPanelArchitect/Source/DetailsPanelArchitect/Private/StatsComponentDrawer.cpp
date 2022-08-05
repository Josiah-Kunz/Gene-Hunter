#define LOCTEXT_NAMESPACE "StatsComponentDrawer"

#include "StatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "MathUtil.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"

TSharedRef<IDetailCustomization> StatsComponentDrawer::MakeInstance()
{
	return MakeShareable(new StatsComponentDrawer);
}

void StatsComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get object
	UStatsComponent* StatsComponent = GetStatsComponent(DetailBuilder);

	// Get useful limits
	float Padding = 2;
	float MaxWidth = 125 - 2*Padding;
	float MaxStatValue = MaxStat(StatsComponent, EStatValueType::Current, false);
	float MaxPercentValue = MaxStat(StatsComponent, EStatValueType::Current, true);


	/*
	SNew(SEditableTextBox)
		.Text(FText::FromString(FString::SanitizeFloat(StatsComponent->Health.GetCurrentValue())))
		*/
		

	// Define macro (if not for GET_MEMBER_NAME_CHECKED, you could do this as a function
#define CURRENT_STAT_PROPERTY(TargetStat, ValueMember, ValueMax) \
	TSharedPtr<IPropertyHandle> Handle##TargetStat = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UStatsComponent, TargetStat)); \
	IDetailPropertyRow* Row##TargetStat = DetailBuilder.EditDefaultProperty(Handle##TargetStat); \
	Row##TargetStat->CustomWidget() \
		.NameContent()[ \
			SNew(SOverlay) \
			+SOverlay::Slot()[ \
				SNew(STextBlock) \
					.Text(FText::FromString(StatsComponent->TargetStat.Abbreviation())) \
				] \
			+SOverlay::Slot()[ \
				SNew(SEditableTextBox) \
					.Text(FText::FromString(FString::SanitizeFloat(StatsComponent->TargetStat.ValueMember))) \
				] \
				.HAlign(HAlign_Right) \
			] \
		.ValueContent()[ \
			SNew(SOverlay) \
			+SOverlay::Slot()[ \
				SNew(SColorBlock) \
					.Color(FLinearColor::Black) \
				] \
			+SOverlay::Slot()[ \
				SNew(SColorBlock) \
					.Color(StatsComponent->TargetStat.Color()) \
					.Size(FVector2D{MaxWidth * StatsComponent->TargetStat.ValueMember / ValueMax, 10}) \
				] \
				.HAlign(HAlign_Left) \
				.Padding(Padding) \
			];

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