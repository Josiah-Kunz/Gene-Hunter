#pragma once

#include "CoreMinimal.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "Outlets/RecalculateStatsOutlet.h"
#include "PermStatMod.generated.h"

/**
 * To be inherited by anything that modifies a permanent stat. Examples are PermStatMod (a Mutation) and FullBloom (a
 * PositiveAura).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class MUTATIONCOMPONENT_API UPermStatMod : public UMutationComponent
{
	GENERATED_BODY()

	UPermStatMod();

#pragma region Static (public) variables

public:
	
	inline static constexpr float PhAIncrease = 15;
	inline static constexpr float DefDecrease = 10;

#pragma endregion

#pragma region Public variables

public:

	/**
	 * Since the primary goal of this Mutation is to modify stats, we'll need this.
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
	 * Modifies the stat according to how this effect should work. For example, if InStat is PhA, it increases it by
	 * PhAIncrease.
	 *
	 * @param Scale If adding the component, this should be 1. If removing the component, this should be -1.
	 */
	void ModifyStat(const EStatEnum InStat, const bool bResetCurrent, const int8 Scale) const;
	

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

