#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "StatMod.h"
#include "Outlets/RecalculateStatsOutlet.h"
#include "PermStatMod.generated.h"

/**
 * To be inherited by anything that modifies a permanent stat. Examples are PermStatMod (a Mutation) and FullBloom (a
 * PositiveAura).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UPermStatMod : public UEffectComponent
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
	FAfterRecalculateStatsDelegate Delegate;

	/**
	 * This is the function that binds to the aforementioned Delegate.
	 */
	UFUNCTION(BlueprintCallable)
	void AfterRecalculateStats(const EStatEnum InStat, const bool bResetCurrent, const float OriginalCurrent,
		const float OriginalPermanent);

private:

	/**
	 * Modifies the stat according to how this effect should work. This is based on how the FStatMod is set up.
	 *
	 * @param Scale If adding the component, this should be 1. If removing the component, this should be -1.
	 */
	void ModifyStat(const EStatEnum InStat, const int8 Scale, const bool bResetCurrent) const;

	/**
	 * Gets all StatMods like:
	 *	PhA +15% | Def -10%
	 */
	virtual FText GetDescriptionText();

#pragma endregion

#pragma region Overrides

public:

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual void Silence() override;

	virtual void Unsilence() override;

#pragma endregion
	
};

