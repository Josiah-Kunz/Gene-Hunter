

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlantRowAssetTwo.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UPlantRowAssetTwo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText DisplayName;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float FlowerRadius = 0.5f;
};
