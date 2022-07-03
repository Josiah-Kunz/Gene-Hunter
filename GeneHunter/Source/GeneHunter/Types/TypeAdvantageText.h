

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TypeAdvantageText.generated.h"

UENUM(BlueprintType)
enum class TAText : uint8
{
	DevNote		UMETA(DisplayName = "DevNote"),
	Description	UMETA(DisplayName = "Description"),
	FlavorText	UMETA(DisplayName = "FlavorText"),
};
