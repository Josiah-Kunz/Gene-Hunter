/*
#pragma once

#include "CoreMinimal.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "DetailsPanelArchitect/Public/DPAButton.h"
#include "DetailWidgetRow.h"

class DPAButtonDrawer : public IDetailCustomization
{

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

private:

	DPAButton* Button;

	DPAButton* GetCurrentDPAButton(IDetailLayoutBuilder& DetailBuilder);

	FReply InvokeOnClickedRaw() const;

};*/