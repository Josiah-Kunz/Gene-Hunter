

#pragma once

#include "CoreMinimal.h"
#include "UI/Public/SupportingText.h"
#include "AttackModifier.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FAttackModifier
{
	GENERATED_BODY()
public:
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float Modifier = 1;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FSupportingText SupportingText;
	
};
