#pragma once

#include "Blueprint/WidgetTree.h"
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetFunctionLibrary.generated.h"

/**
 * A library just for custom constants.
 */
UCLASS()
class BPLIBRARIES_API UWidgetFunctionLibrary : public UBlueprintFunctionLibrary
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
	 *		UButton* Button = Cast<UButton>(GetChildOfType(this, UButton::StaticClass()));
	 */
	UFUNCTION(BlueprintCallable)
	static UWidget* GetChildOfType(const UUserWidget* Parent, const TSubclassOf<UWidget> WidgetClass);

	/**
	 * If the input color is "dark", this returns white; otherwise, returns black. Useful for getting
	 * text colors on a background.
	 */
	UFUNCTION(BlueprintCallable)
	static FLinearColor CorrespondingTextColor(const FLinearColor& Color);

	/**
	 * Returns the opposite of CorrespondingTextColor. That is, f the input color is "dark", this returns black;
	 * otherwise, returns white. Useful for getting text outline colors on a background.
	 */
	UFUNCTION(BlueprintCallable)
	static FLinearColor CorrespondingOutlineColor(const FLinearColor& Color);
	
};