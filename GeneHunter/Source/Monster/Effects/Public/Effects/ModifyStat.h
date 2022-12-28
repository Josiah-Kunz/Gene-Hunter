#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "StatsComponent/Public/ModificationMode.h"
#include "StatsComponent/Public/StatValueType.h"

#include "ModifyStat.generated.h"

/**
 * An FEffect that can modify a single stat on either UStatsComponent::RecalculateStats, UStatsComponent::ModifyStats,
 *	or both.
 */
USTRUCT(Blueprintable)
struct EFFECTS_API FModifyStat : public FEffect
{
	GENERATED_BODY()

#pragma region Public variables

public:
	
	float Value;
	EModificationMode Mode;
	EStatValueType ValueType;

	UENUM(BlueprintType)
	enum class ETrigger : uint8
	{
		None				UMETA(Tooltip="No modification (this FEffect does nothing)."),
		RecalculateStats	UMETA(Tooltip="Modification triggered via UStatsComponent::RecalculateStats"),
		ModifyStats			UMETA(Tooltip="Modification triggered via UStatsComponent::ModifyStatsInternal"),
		Both				UMETA(Tooltip="Modification triggered via RecalculateStats and ModifyStats."),
	};
	
	ETrigger Trigger;

	
	
};

