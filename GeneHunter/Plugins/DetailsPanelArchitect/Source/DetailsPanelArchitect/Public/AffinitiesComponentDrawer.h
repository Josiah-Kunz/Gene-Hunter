#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "AffinitiesComponent.h"
#include "Widgets/SCanvas.h"


class AffinitiesComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	
	UAffinitiesComponent* AffinitiesComponent = nullptr;

	TArray<UType*> AllTypes;
	TArray<TSharedPtr<FString>> TypeNames;


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

#pragma region Private customization functions

	virtual void CustomizeMaxUsableAffinities(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

	virtual void CustomizeAffinities(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);
	
	virtual void DrawAffinity(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
		FAffinity& Affinity);

	virtual void DrawArrayMutator(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

#pragma endregion

#pragma region Public utility functions

public:
	
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	static bool UserCommitted(const ETextCommit::Type CommitType);

	UType* GetTypeByName(const FString* TypeName);

	TFunction<void(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)> OnComboBoxChanged(
		IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UAffinitiesComponent* GetAffinitiesComponent(const IDetailLayoutBuilder& DetailBuilder);

	// Do we need this??
	TArray<TSharedPtr<UType*, ESPMode::ThreadSafe>> GetTypes() const;

	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> GetTypeNames();

	TSharedPtr<SHorizontalBox> AffinityValueCanvas(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity) const;

	FSimpleDelegate CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity) const;

	bool CanModifyAffinity(const FAffinity& Affinity) const;

#pragma endregion
	
};
