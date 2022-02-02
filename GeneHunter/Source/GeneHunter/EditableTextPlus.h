

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableText.h"
#include "EditableTextPlus.generated.h"

// Delegates for changing the text by code or user.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextChangedProgrammaticEvent, const FText&, NewText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditableTextChangedInteractiveEvent, const FText&, NewText);

/**
 * A class that custom-expands EditableText (e.g., splits OnTextChanged into OnChangedByCode and OnChangedByUser).
 */
UCLASS(meta=(DisplayName="EditableText+"))
class GENEHUNTER_API UEditableTextPlus : public UEditableText
{
	GENERATED_BODY()

	/** Overrides and aliases (sort of). */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void HandleOnTextChangedOverride(const FText& InText);
	
public:
	
	/** Called whenever the text is changed programmatically (by code). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Widget Event", meta=(DisplayName="OnChangedByCode (EditableText+)"))
	FOnEditableTextChangedProgrammaticEvent OnChangedByCode;

	/** Called whenever the text is changed interactively (by the user). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Widget Event", meta=(DisplayName="OnChangedByUser (EditableText+)"))
	FOnEditableTextChangedInteractiveEvent OnChangedByUser;

	/** Only true when SetTextProgrammatic is called. Promptly set to false after HandleOnTextChangedOverride is called. */
	bool bChangedProgrammatic;

	/*
	 * Sets the text as usual by calling the base SetText. However, it also allows OnChangedByCode to be called.
	 */
	UFUNCTION(BlueprintCallable)
	void SetTextProgrammatic(const FText& NewText);
	
	/*
	 * Alias for SetTextProgrammatic.
	 */
	UFUNCTION(BlueprintCallable)
	void SetTextByCode(const FText& NewText);

	/*
	 * Sets the text as usual by calling the base SetText. However, it also allows OnChangedByUser to be called.
	 */
	UFUNCTION(BlueprintCallable)
	void SetTextInteractive(const FText& NewText);

	/*
	 * Alias for SetTextInteractive.
	 */
	UFUNCTION(BlueprintCallable)
	void SetTextByUser(const FText& NewText);

	/*
	 * Allows the user to set the font color in the Blueprint (which, oddly enough, isn't standard).
	 */
	UFUNCTION(BlueprintCallable)
	void SetFontColor(const FLinearColor& Color);
};
