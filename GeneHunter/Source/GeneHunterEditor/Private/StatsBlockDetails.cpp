


#include "StatsBlockDetails.h"

#define LOCTEXT_NAMESPACE "StatsBlockDetails"

TSharedRef<IDetailCustomization> FStatsBlockDetails::MakeInstance()
{
	return MakeShareable(new FStatsBlockDetails);
}

void FStatsBlockDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	IDetailCategoryBuilder& StatsCat = DetailBuilder.EditCategory("Stats", LOCTEXT("CatName", "Stats") ,ECategoryPriority::Important);
	StatsCat.AddCustomRow(LOCTEXT("Keyword", "Shuffle"))
		.NameContent()[
			SNew(STextBlock)
				.Text(LOCTEXT("NameText", "Reassign Materials"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent()[
			SNew(SButton)
				.Text(LOCTEXT("ButtonText", "Shuffle"))
				.OnClicked_Raw(this, &FStatsBlockDetails::EditObjects)
			];
}

FReply FStatsBlockDetails::EditObjects()
{

	for(TWeakObjectPtr<UObject> Object : ObjectsToEdit)
	{
		// Guard
		if (!Object.IsValid()) continue;

		// Get
		UStatsBlock* StatsBlock = Cast<UStatsBlock>(Object.Get());

		// Gaurd again
		if (!StatsBlock) continue;;

		// Do stuff
		UE_LOG(LogTemp, Warning, TEXT("YAY!"))
	}
	
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE