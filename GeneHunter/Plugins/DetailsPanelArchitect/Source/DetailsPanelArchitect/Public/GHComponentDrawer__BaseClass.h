#pragma once
#include "DetailLayoutBuilder.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PropertyEditor/Public/IDetailCustomization.h"


class GHComponentDrawer__BaseClass : public IDetailCustomization
{

/**
 * NonUName is, e.g., "StatsComponent" for a UStatsComponent. File+class name should be "NonUNameDrawer". This macro:
 *	- Defines the (private) variable NonUName (e.g., "StatsComponent")
 *	- Defines MakeInstance()
 *	- Defines GetNonUName(IDetailLayoutBuilder& DetailBuilder)
 *	- Defines (private) ObjectsToEdit
 *	- Defines SaveAndRefresh
 */
#define COMPONENT_SETUP(NonUName) \
	private: \
	U##NonUName * NonUName = nullptr; \
	public: \
	static TSharedRef<IDetailCustomization> MakeInstance(){ \
		return MakeShareable(new NonUName##Drawer); \
	}; \
	U##NonUName * Get##NonUName##(IDetailLayoutBuilder& DetailBuilder) { \
		DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit); \
		if (ObjectsToEdit.Num() == 0) return nullptr; \
		const TWeakObjectPtr<UObject> Object = ObjectsToEdit[0]; \
		if (!Object.IsValid()) return nullptr; \
		NonUName = Cast<U##NonUName >(Object.Get()); \
		return NonUName; \
	}; \
	private: \
	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit; \
	public: \
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const{ \
		UKismetSystemLibrary::TransactObject( NonUName ); \
		DetailBuilder.ForceRefreshDetails(); \
	};

public:

	/** Converts the value to FText depending on whether or not its an integer. */
	static FText FloatToFText(const float Value, const bool bIntegerOnly){
		return FText::FromString(
			bIntegerOnly ?
			FString::FromInt(FMath::RoundToInt(Value)) :
			FString::SanitizeFloat(Value));
	};

	/**
	 * Gets the fraction [0, ...) between two int32s. This is useful for, e.g., the level bar, especially at max level
	 * when the denominator would be zero.
	 */
	static float GetFraction(const int32 Numerator, const int32 Denominator)
	{
		// Avoid divide by zero error and negative bars
		if (Denominator <= 0)
		{
			return 1;
		}

		// Convert to float
		return Numerator/static_cast<float>(Denominator);
	};

};