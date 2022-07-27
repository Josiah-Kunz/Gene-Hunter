#pragma once

#include "CoreMinimal.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "GeneHunter/StatsBlock/StatsBlock.h"

class FStatsBlockDetailsPanel : public IDetailCustomization
{

public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	FReply EditObjects();

	FReply PrintBST();

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;
};