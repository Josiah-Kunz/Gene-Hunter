#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "AffinitiesComponent.h"


class AffinitiesComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	
	UAffinitiesComponent* AffinitiesComponent = nullptr;


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

#pragma region Private customization functions

#pragma endregion

#pragma region Public utility functions

public:
	
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	static bool UserCommitted(const ETextCommit::Type CommitType);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UAffinitiesComponent* GetAffinitiesComponent(const IDetailLayoutBuilder& DetailBuilder);

#pragma endregion
	
};
