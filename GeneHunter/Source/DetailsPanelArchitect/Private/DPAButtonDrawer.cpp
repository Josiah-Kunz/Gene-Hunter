#include "DPAButtonDrawer.h"

#include "IDetailChildrenBuilder.h"
#include "IHeadMountedDisplay.h"

#define LOCTEXT_NAMESPACE "DPAButtonDrawer"

TSharedRef<IPropertyTypeCustomization> DPAButtonDrawer::MakeInstance()
{
	return MakeShared<DPAButtonDrawer>();
}

void DPAButtonDrawer::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

	// Get button
	if (!StructPropertyHandle->IsValidHandle() || !StructPropertyHandle->GetProperty())
		return;
	TArray<void*> RawStructData;
	StructPropertyHandle->AccessRawData(RawStructData);
	if (RawStructData.Num() <= 0)
		return;
	Button = static_cast<FDPAButton*>(RawStructData[0]);
	if (!Button)
		return;

	// Set defaults (if not handled already; this just really ensures no nonsense)
	Button->ConstructDefaultValues();


	HeaderRow
			.OverrideResetToDefault(FResetToDefaultOverride::Hide())
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


/*
	
	
	// NameContent may or may not be used
#define NAME_CONTENT() \
	SNew(STextBlock) \
			.Text(Button->LabelText) \
			.Font(Button->LabelFont)

	// ValueContent will be used fo sho
#define VALUE_CONTENT() \
	SNew(SButton) \
			.Text(Button->ButtonText) \
			.OnClicked_Raw(this, &DPAButtonDrawer::InvokeOnClickedRaw)

	// Slate
	if (Button->LabelText.IsEmptyOrWhitespace())
		HeaderRow
		.OverrideResetToDefault(FResetToDefaultOverride::Hide())
			.ValueContent()[VALUE_CONTENT()];
	else
		HeaderRow
		.OverrideResetToDefault(FResetToDefaultOverride::Hide())
			.NameContent()[NAME_CONTENT()]
			.ValueContent()[VALUE_CONTENT()];*/
}

void DPAButtonDrawer::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	// TODO:
	// Function call options here?
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
	if (!Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button does not exist!"));
		return FReply::Unhandled();
	}
	Button->OnClicked_Raw();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE