#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "Stat.h"
#include "StatsComponent.h"
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

	// The thing to attach to
	// ----------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;

	// How to modify
	// -------------
	
	FStat* Stat;
	
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
	
	ETrigger Trigger = ETrigger::RecalculateStats;

	// Delegation variables
	// --------------------
	
	std::function<void(FStat*, const bool)> RecalculateLambda = [this](FStat* InStat, const bool bResetCurrent)
	{
		if (InStat->Name().Equals(Stat->Name()))
			InStat->ModifyValue(Value, ValueType, Mode);
	};
	UStatsComponent::FRecalculateStatsDelegate RecalculateStatsDelegate;

	std::function<void(FStat*, const float, const EStatValueType, const EModificationMode)> ModifyLambda =
		[this](FStat* InStat, const float InValue, const EStatValueType InValueType, const EModificationMode InMode)
		{
			if (InStat->Name().Equals(Stat->Name()))
				InStat->ModifyValue(Value, ValueType, Mode);
		};
	UStatsComponent::FModifyStatDelegate ModifyStatDelegate;
	
	virtual void OnAttach() override;

	virtual void OnDetach() override;
};

