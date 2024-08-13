#pragma once

#include "CoreMinimal.h"
#include "Type.h"

#include "Affinity.generated.h"

USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FAffinity
{
	GENERATED_BODY()

public:

	/**
	 * If locked, the Monster *must* have at least one point in this Affinity. It is a defining Type for the Monster.
	 */
	bool IsLocked() const;

	/**
	 * If locked, the Monster *must* have at least one point in this Affinity. It is a defining Type for the Monster.
	 */
	void SetLockedState(const bool bLockedState);
	
	/**
	 * The Type that the Monster might have an affinity for.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	UType* Type = nullptr;

	uint8 GetCurrentPoints() const;
	
	void SetCurrentPoints(const uint8 NewPoints);

	uint8 GetMaxPoints() const;

	void SetMaxPoints(const uint8 NewMax);

	/**
	 * If there are >1 current points, the Same Type Attack Bonus is 1.5x. Otherwise, it's 1.0x.
	 */
	float GetSTAB() const;

private:

	/**
	 * If locked, the Monster *must* have at least one point in this Affinity. It is a defining Type for the Monster.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	bool bLocked = false;

	/**
	 * The current number of points put into this Affinity.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	uint8 CurrentPoints = 0;

	/**
	 * The maximum number of possible points to put into this Affinity.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	uint8 MaxPoints = 3;
	
};
