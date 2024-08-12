#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "MoveCategory.h"
#include "MoveContact.h"
#include "SupportingText.h"
#include "Type.h"

#include "MoveData.generated.h"

USTRUCT(Blueprintable)
struct BATTLEENGINE_API FMoveData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	float BasePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	float BaseCooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveCategory Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveContact Contact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	TArray<TSubclassOf<UEffectComponent>> EffectsToInflict;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	FFloatRange RandomRange = FFloatRange{0.85f, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	FSupportingText SupportingText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	TArray<UType*> Types;

protected:
	
	bool bCanCategoryDoDamage() const
	{
		return Category == EMoveCategory::Physical || 
			   Category == EMoveCategory::Special || 
			   Category == EMoveCategory::Healing;
	}

	
};
