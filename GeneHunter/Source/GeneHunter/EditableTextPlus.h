

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditableTextPlus.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UEditableTextPlus : public UUserWidget
{
	GENERATED_BODY()

public:
	//overrides
	virtual void SynchronizeProperties() override;

	/**
	 * This is called after a widget is constructed and properties are synchronized.
	 * It can also be called by the editor to update modified state.
	 * Override this event in blueprint to update the widget after a default 
	 * property is modified.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "User Interface")
	void OnSynchronizeProperties();

	UFUNCTION(BlueprintCallable, Category = "User Interface")
	void SynchronizeProperty(UWidget* Widget);
};
