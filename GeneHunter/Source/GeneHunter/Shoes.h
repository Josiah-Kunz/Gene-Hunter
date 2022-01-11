

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Shoes.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UShoes : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float ShoeSize = 10.5f;
	
};
