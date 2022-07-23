/*
#include "DPAButtonDrawer.h"

#include <windows.foundation.collections.h>

#include "DetailLayoutBuilder.h"

#define LOCTEXT_NAMESPACE "DPAButtonDrawer"

TSharedRef<IDetailCustomization> DPAButtonDrawer::MakeInstance()
{
	return MakeShareable(new DPAButtonDrawer);
}

void DPAButtonDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// Get das button
	Button = GetCurrentDPAButton(DetailBuilder);
	if (!Button) return;

	// Ensure non-nonsense
	Button->ConstructDefaultValues();
	
	// Modify category slate-style
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		Button->CategoryName, Button->LocalizedDisplayName, Button->CategoryPriority);

	// Visuals slate-style
	Category.AddCustomRow(Button->RowFilterString)
		.NameContent()[
			SNew(STextBlock)
				.Text(Button->LabelText)
				.Font(Button->LabelFont)
			]
		.ValueContent()[
			SNew(SButton)
				.Text(Button->ButtonText)
				.OnClicked_Raw(this, &DPAButtonDrawer::InvokeOnClickedRaw)
			];
}

DPAButton* DPAButtonDrawer::GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	DPAButton* Ret = Cast<DPAButton>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;

	// Return
	return Ret;
}

FReply DPAButtonDrawer::InvokeOnClickedRaw() const
{
	Button->OnClicked_Raw();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE*/