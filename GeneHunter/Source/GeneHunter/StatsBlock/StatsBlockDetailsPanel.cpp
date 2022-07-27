#include "StatsBlockDetailsPanel.h"

#define LOCTEXT_NAMESPACE "StatsBlockDetailsPanel"

TSharedRef<IDetailCustomization> FStatsBlockDetailsPanel::MakeInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Made something"))
	return MakeShareable(new FStatsBlockDetailsPanel);
}

void FStatsBlockDetailsPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get category
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	IDetailCategoryBuilder& StatsCat = DetailBuilder.EditCategory("POOP", LOCTEXT("CatName", "POOP") ,ECategoryPriority::Important);

	// Display stats
	/*
	StatsCat.AddCustomRow(LOCTEXT("Keyword", "Stat Values"))
		.WholeRowContent()[
			SNew(SBorder)
				.ColorAndOpacity(FLinearColor(1.0f, 0, 0, 1))
			]
		.NameContent()[
			SNew(STextBlock)
				.Text(LOCTEXT("NameText", "Print BST"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
	;
	*/
	StatsCat.AddCustomRow(LOCTEXT("Keyword", "Print BST"))
		.NameContent()[
			SNew(STextBlock)
				.Text(LOCTEXT("NameText", "Print BST"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent()[
			SNew(SButton)
				.Text(LOCTEXT("ButtonText", "Print BST"))
				.OnClicked_Raw(this, &FStatsBlockDetailsPanel::PrintBST)
			];
}

FReply FStatsBlockDetailsPanel::EditObjects()
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

FReply FStatsBlockDetailsPanel::PrintBST()
{

	for(TWeakObjectPtr<UObject> Object : ObjectsToEdit)
	{
		// Guard
		if (!Object.IsValid()) continue;

		// Get
		UStatsBlock* StatsBlock = Cast<UStatsBlock>(Object.Get());

		// Gaurd again
		if (!StatsBlock) continue;

		// Print
		UE_LOG(LogTemp, Warning, TEXT("BST: %s"),
		 *FString::SanitizeFloat(StatsBlock->BaseStatTotal())
		 );

	}
	
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE