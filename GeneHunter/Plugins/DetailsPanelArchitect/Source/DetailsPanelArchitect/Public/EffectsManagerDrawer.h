#pragma once
#include "DetailLayoutBuilder.h"
#include "EffectsManager.h"
#include "PropertyEditor/Public/IDetailCustomization.h"


class IEffectsManagerDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	
	UEffectsManager* EffectsManager = nullptr;

	TArray<UEffectComponent*> AllEffects;
	TArray<TSharedPtr<FString>> AttachedEffectNames;

	const FString CategoryName = "Effects";


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	 * Where the magic happens!
	 */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

public:

	/**
	 * Customizes the Effects available to the Monster.
	 */
	virtual void DrawEffectsList(IDetailLayoutBuilder& DetailBuilder);

public:

	/**
	 * Marks the current object as dirty and refreshes the detail builder.
	 */
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;
	
private:

	/**
	 * Retrieves the star of the show!
	 */ 
	UEffectsManager* GetEffectsManager(const IDetailLayoutBuilder& DetailBuilder);
	
};
