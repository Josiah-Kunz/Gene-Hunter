

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
class UI_API UEditableTextPlus : public UEditableText
{
	GENERATED_BODY()
	
#pragma region Enhanced variables

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Text Options" )
	bool bNumeric;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Text Options", meta=(EditCondition="bNumeric") )
	bool bIntegerOnly;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Text Options", meta=(EditCondition="bNumeric") )
	bool bCanBeNegative = true;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Text Options", meta=(EditCondition="bNumeric") )
	bool bCanBeZero = true;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Text Options", meta=(EditCondition="bNumeric") )
	bool bCanBePositive = true;

#pragma endregion

#pragma region Text changing events

	/** Overrides and aliases (sort of). */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void HandleOnTextChangedOverride(const FText& InText);
	
public:
	
	/** Called whenever the text is changed programmatically (by code). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Widget Event")
	FOnEditableTextChangedProgrammaticEvent OnChangedByCode;

	/** Called whenever the text is changed interactively (by the user). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Widget Event")
	FOnEditableTextChangedInteractiveEvent OnChangedByUser;

	/** Only true when SetTextProgrammatic is called. Promptly set to false after HandleOnTextChangedOverride is called. */
	bool bChangedProgrammatic;

	/**
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

#pragma  endregion

#pragma region Text manipulation

	/*
	 * Allows the user to set the font color in the Blueprint (which, oddly enough, isn't standard).
	 */
	UFUNCTION(BlueprintCallable)
	void SetFontColor(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable, BlueprintPure=true)
	void TextAsFloat(float& Float);

#pragma endregion
};
