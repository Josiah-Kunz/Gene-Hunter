#pragma once

#include "CoreMinimal.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "DPAButton.h"
#include "DetailWidgetRow.h"

class FDPAButtonDrawer : public IDetailCustomization
{

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

private:

	FDPAButton* DPAButton;

	FDPAButton* GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder);

	FReply InvokeOnClickedRaw() const;

};