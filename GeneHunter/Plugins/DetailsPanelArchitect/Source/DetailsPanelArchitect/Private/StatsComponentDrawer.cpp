#define LOCTEXT_NAMESPACE "StatsComponentDrawer"

#include "StatsComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> StatsComponentDrawer::MakeInstance()
{
	return MakeShareable(new StatsComponentDrawer);
}

void StatsComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get object
	UStatsComponent* StatsComponent = GetStatsComponent(DetailBuilder);
	
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

#undef LOCTEXT_NAMESPACE