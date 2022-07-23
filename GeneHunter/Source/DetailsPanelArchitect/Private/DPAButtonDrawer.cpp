#include "DPAButtonDrawer.h"

#define LOCTEXT_NAMESPACE "DPAButtonDrawer"

TSharedRef<IPropertyTypeCustomization> DPAButtonDrawer::MakeInstance()
{
	return MakeShared<DPAButtonDrawer>();
}

void DPAButtonDrawer::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
/*
	// Get das button
	FDPAButton B;
	StructPropertyHandle->GetValueData()
	if (!Button) return;

	// Ensure non-nonsense
	Button->ConstructDefaultValues();

	// Slate
	
	HeaderRow
		.NameContent()[
			SNew(STextBlock)
				.Text(Button->LabelText)
				.Font(Button->LabelFont)
			]
		.ValueContent()[
			SNew(SButton)
				.Text(Button->ButtonText)
				.OnClicked_Raw(this, &DPAButtonDrawer::InvokeOnClickedRaw)
			];*/

	HeaderRow
		.NameContent()[
			SNew(STextBlock)
				.Text(FText::FromString("OY"))
			]
		.ValueContent()[
			SNew(SButton)
				.Text(FText::FromString("3head"))
			];
}

void DPAButtonDrawer::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

/*
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

*/

/*
FDPAButton* DPAButtonDrawer::GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	FDPAButton* Ret = Cast<FDPAButton>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;

	// Return
	return Ret;
}*/

FReply DPAButtonDrawer::InvokeOnClickedRaw() const
{
	Button->OnClicked_Raw();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE