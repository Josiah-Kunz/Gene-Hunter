#pragma once

#include "CoreMinimal.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "StatsComponent.h"
#include "DetailWidgetRow.h"

class StatsComponentDrawer : public IDetailCustomization
{

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

	UStatsComponent* GetStatsComponent(IDetailLayoutBuilder& DetailBuilder);
	
};