#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "PositiveAuraComponent.h"
#include "Outlets/ModifyStatOutlet.h"
#include "FullBloom.generated.h"

/**
 * +20% max health
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class POSITIVEAURACOMPONENT_API UFullBloom : public UPositiveAuraComponent
{
	GENERATED_BODY()

	UFullBloom();

#pragma region Static (public) variables

public:

	/**
	 * Increase health by this amount.
	 */
	inline static constexpr float HPIncrease = 20;

#pragma endregion

#pragma region Public variables

public:

	/**
	 * Since the primary goal of this effect is to modify stats, we'll need this.
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

#pragma endregion

#pragma region Overrides

public:

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual void Silence() override;

	virtual void Unsilence() override;

#pragma endregion
	
#pragma region Private functions



#pragma endregion
	
};

