#include "EffectsManagerDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Views/SListView.h"

#define LOCTEXT_NAMESPACE "IEffectsManagerDrawer"

#pragma region Boilerplate

TSharedRef<IDetailCustomization> IEffectsManagerDrawer::MakeInstance()
{
	return MakeShareable(new IEffectsManagerDrawer);
}

void IEffectsManagerDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	EffectsManager = GetEffectsManager(DetailBuilder);

}

#pragma endregion

void IEffectsManagerDrawer::DrawEffectsList(IDetailLayoutBuilder& DetailBuilder)
{
	/*
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);

	const TArray<UEffectComponent*> AttachedEffects = EffectsManager->GetAttachedEffects();
	Category.AddCustomRow(LOCTEXT("Keyword", "Effects List")).WholeRowContent()[
		SNew(SListView<TSharedPtr<FString>>)
			.ListItemsSource(&AttachedEffectNames)
	]
	;
	*/
}

void IEffectsManagerDrawer::SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const
{
	UKismetSystemLibrary::TransactObject(EffectsManager);
	DetailBuilder.ForceRefreshDetails();
}

UEffectsManager* IEffectsManagerDrawer::GetEffectsManager(const IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	const TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	UEffectsManager* Ret = Cast<UEffectsManager>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;

	// Return
	return Ret;
}


#undef LOCTEXT_NAMESPACE
