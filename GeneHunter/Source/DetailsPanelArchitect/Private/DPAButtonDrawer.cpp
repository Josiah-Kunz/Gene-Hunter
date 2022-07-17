#include "DPAButtonDrawer.h"

#define LOCTEXT_NAMESPACE "DPAButtonDrawer"

TSharedRef<IDetailCustomization> FDPAButtonDrawer::MakeInstance()
{
	return MakeShareable(new FDPAButtonDrawer);
}

void FDPAButtonDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get das button
	DPAButton = GetCurrentDPAButton(DetailBuilder);
	if (!DPAButton) return;

	// Ensure non-nonsense
	DPAButton->ConstructDefaultValues();
	
	// Modify category slate-style
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		DPAButton->CategoryName, DPAButton->LocalizedDisplayName, DPAButton->CategoryPriority);

	// Visuals slate-style
	Category.AddCustomRow(DPAButton->RowFilterString)
		.NameContent()[
			SNew(STextBlock)
				.Text(DPAButton->LabelText)
				.Font(DPAButton->LabelFont)
			]
		.ValueContent()[
			SNew(SButton)
				.Text(DPAButton->ButtonText)
				.OnClicked_Raw(this, &FDPAButtonDrawer::InvokeOnClickedRaw)
			];
}

FDPAButton* FDPAButtonDrawer::GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	FDPAButton* Button = Cast<FDPAButton>(Object.Get());

	// Guard again
	if (!Button) return nullptr;

	// Return
	return Button;
}

FReply FDPAButtonDrawer::InvokeOnClickedRaw() const
{
	DPAButton->OnClicked_Raw->operator()();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE