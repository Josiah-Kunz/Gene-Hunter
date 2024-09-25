#pragma once

#include "CoreMinimal.h"
#include "SupportingText.generated.h"

USTRUCT(Blueprintable)
struct UI_API FSupportingText
{
	GENERATED_BODY()

#pragma region Static data

public:
	
	const static TMap<FString, FString> StaticReplacements;

	static FText DoReplacements(const FText& Text);
	
#pragma endregion

#pragma region Instanced data
	
public:

	/**
	 * The DevNote is for developers and is in-editor only. It will not be displayed in-game.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText DevNote;

	/**
	 * Short text that will be displayed in-game. This gives an overview that can be quickly glanced at, e.g., when
	 * looking at a list or in combat.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Summary;

	/**
	 * The Description is helpful text that will be displayed in-game. It's a long-form version of Summary that gives
	 * a lot more detail, e.g., when planning.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Description;

	/**
	 * The FlavorText is funny or lore-based text. It is pseudo-hidden in-game (e.g., on hover of the description). 
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText FlavorText;

#pragma endregion
	
};
