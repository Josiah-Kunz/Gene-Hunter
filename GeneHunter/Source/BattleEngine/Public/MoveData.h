#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "MoveCategory.h"
#include "MoveContact.h"
#include "SupportingText.h"
#include "Type.h"

#include "MoveData.generated.h"

/**
 * An asset that holds static data on a Move. Think of it as a Pokedex entry.
 */
UCLASS()
class BATTLEENGINE_API UMoveData : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Variables

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	float BasePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	float BaseCooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveCategory Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveContact Contact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(Tooltip="If blank, this is the same as the asset name. Really only useful for special characters or a dynamic name."))
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(Tooltip="The effects and the percentage to be inflicted. >100 means it's a sure thing."))
	TMap<TSubclassOf<UEffectComponent>, float> EffectsToInflict;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	FFloatRange RandomRange = FFloatRange{0.85f, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	FSupportingText SupportingText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	TArray<UType*> Types;

#pragma endregion

#pragma region Functions
	
protected:
	
	bool bCanCategoryDoDamage() const
	{
		return Category == EMoveCategory::PhysicalDamage || 
			   Category == EMoveCategory::SpecialDamage || 
			   Category == EMoveCategory::SpecialHealing;
	}

#pragma endregion
	
};
