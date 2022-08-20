#pragma once

#include "CoreMinimal.h"
#include "SupportingText.generated.h"

USTRUCT(Blueprintable)
struct UI_API FSupportingText
{
	GENERATED_BODY()
public:

	/*
	 * The DevNote is for developers and is in-editor only. It will not be displayed in-game.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText DevNote;

	/*
	 * The Description is helpful text that will be displayed in-game.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Description;

	/*
	 * The FlavorText is funny or lore-based text. It is pseudo-hidden in-game (e.g., on hover of the description). 
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText FlavorText;
	
};
