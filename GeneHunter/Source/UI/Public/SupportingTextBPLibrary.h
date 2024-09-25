// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupportingText.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SupportingTextBPLibrary.generated.h"

/**
 * Because stupid UE5 doesn't support stupid USTRUCTs having stupid functions and stupid me no think ahead -_-
 */
UCLASS()
class UI_API USupportingTextBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Retrieves the DevNote with replacements made.
	 */
	UFUNCTION(Category = "SupportingText")
	static FText GetDevNoteForDisplay(const FSupportingText& SupportingText);

	/**
	 * Retrieves the Summary with replacements made.
	 */
	UFUNCTION(Category = "SupportingText")
	static FText GetSummaryForDisplay(const FSupportingText& SupportingText);

	/**
	 * Retrieves the Description with replacements made.
	 */
	UFUNCTION(Category = "SupportingText")
	static FText GetDescriptionForDisplay(const FSupportingText& SupportingText);

	/**
	 * Retrieves the FlavorText with replacements made. 
	 */
	UFUNCTION(Category = "SupportingText")
	static FText GetFlavorTextForDisplay(const FSupportingText& SupportingText);
	
};
