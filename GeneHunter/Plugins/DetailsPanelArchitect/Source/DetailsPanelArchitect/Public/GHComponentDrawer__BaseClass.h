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

};