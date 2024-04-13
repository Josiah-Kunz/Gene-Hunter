#pragma once

#include "CoreMinimal.h"
#include "DependentEffectComponent.h"
#include "StatMod.h"
#include "Outlets/RecalculateStatsOutlet.h"
#include "PermStatMod.generated.h"

/**
 * To be used by anything that modifies a permanent stat. Examples are BerserkerGene (a Mutation) and FullBloom (a
 * PositiveAura).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class DEPENDENTEFFECTCOMPONENT_API UPermStatMod : public UDependentEffectComponent
{
	GENERATED_BODY()

	UPermStatMod();

#pragma region Public variables

public:

	/**
	 * The stats that this EffectComponent is responsible for modifying.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<FStatMod> StatMods;

	/**
	 * Since the primary goal is to modify stats, we'll need this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * This is the delegate that attaches to UCombatStatComponent's AfterRecalculateStats Outlet.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FAfterRecalculateStatsDelegate AfterRecalcStatsDelegate;

	/**
	 * This is the function that binds to the aforementioned Delegate.
	 */
	UFUNCTION(BlueprintCallable)
	void AfterRecalculateStats(const EStatEnum InStat, const bool bResetCurrent, const float OriginalCurrent,
		const float OriginalPermanent);

#pragma endregion

#pragma region Public functions

public:
	
	/**
	 * Gets all StatMods like:
	 *	PhA +15% | Def -10%
	 */
	virtual FText GetDescriptionText();

#pragma endregion

#pragma region Overrides

public:

	virtual void SetOwner(UEffectComponent* NewOwner) override;

	virtual FSupportingText GetSupportingText() override;

	virtual void AddEffect() override;

	virtual void RemoveEffect() override;

#pragma endregion

#pragma region Private functions
	
private:

	/**
	 * Modifies the stat according to how this effect should work. This is based on how the FStatMod is set up.
	 *
	 * @param InStat The stat to modify.
	 * @param bIncrease If adding the component, this should be true. If removing the component, this should be false.
	 * @param bResetCurrent if true, reset both permanent and current stats (in that order).
	 */
	void ModifyStat(const EStatEnum InStat, const bool bIncrease, const bool bResetCurrent);

	void AddOrRemoveEffectInternal(const bool bAdding);

#pragma endregion


	
};

