

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "TypeAdvantageEditorEnums.generated.h"

UENUM(BlueprintType)
enum class TAQueueStatus : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Rename	UMETA(DisplayName = "Rename"),
};

UENUM(BlueprintType)
enum class TAText : uint8
{
	DevNote		UMETA(DisplayName = "DevNote"),
	FlavorText	UMETA(DisplayName = "FlavorText"),
};
