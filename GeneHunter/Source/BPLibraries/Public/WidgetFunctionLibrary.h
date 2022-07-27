#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetFunctionLibrary.generated.h"

/**
 * A library just for custom constants.
 */
UCLASS()
class GENEHUNTER_API UWidgetFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Works exactly like ClearChildren, but gives the option to exclude certain children.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void ClearChildrenExcept(UPanelWidget* Widget, const TArray<UWidget*> Exclude);

	/**
	 * Calls DuplicateObject with Outer as Original->GetOuter() (see official docs for further explanation).
	 */
	UFUNCTION(BlueprintCallable)
	static UWidget* Duplicate(const UWidget* Original);

	/**
	 *	Gets the first UWidget* of the specified class among the Parent's children.
	 *	Usage:
	 *		UButton* Button = Cast<UButton>(UGeneHunterBPLibrary::GetChildOfType(this, UButton::StaticClass()));
	 */
	UFUNCTION(BlueprintCallable)
	static UWidget* GetChildOfType(const UUserWidget* Parent, const TSubclassOf<UWidget> WidgetClass);
	
};