
#pragma once

#include "CoreMinimal.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "DetailsPanelArchitect/Public/DPAButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

class DPAButtonDrawer : public IPropertyTypeCustomization
{

#pragma region Boilerplate
	
public:

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//~ Begin IPropertyTypeCustomization
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	//~ End IPropertyTypeCustomization

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

private:

	DPAButton* Button;

	//DPAButton* GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder);

	FReply InvokeOnClickedRaw() const;

};