

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackModifier.h"
#include "Type.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UType : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/**
	 * The name as it is displayed in game.
	 **/
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText DisplayName;
	
	/**
	 * A map of modifiers that this Type gets when attacking other Types.
	 **/
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TMap<UType*, UAttackModifier*> AttackModifiers;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FLinearColor> Colors;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText DevNote;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText FlavorText;
	
};
