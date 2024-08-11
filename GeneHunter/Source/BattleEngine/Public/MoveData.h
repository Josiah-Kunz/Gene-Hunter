#pragma once

#include "CoreMinimal.h"
#include "MoveCategory.h"
#include "MoveContact.h"
#include "MoveData.h"
#include "Type.h"

#include "MoveData.generated.h"

USTRUCT(Blueprintable)
struct BATTLEENGINE_API FMoveData
{
	GENERATED_BODY()

public:

	UPROPERTY(Blueprintable, Category="Move Data")
	float BasePower;

	UPROPERTY(Blueprintable, Category="Move Data")
	EMoveCategory Category;
	
	UPROPERTY(Blueprintable, Category="Move Data")
	EMoveContact Contact;

	UPROPERTY(Blueprintable, Category="Move Data")
	FFloatRange RandomRange = FFloatRange{0.85f, 1};

	UPROPERTY(Blueprintable, Category="Move Data")
	FSupportingText SupportingText;
	
	UPROPERTY(Blueprintable, Category="Move Data")
	TArray<UType*> Types;
	
};
