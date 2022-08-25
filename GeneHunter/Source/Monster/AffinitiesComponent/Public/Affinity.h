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

	int GetCurrentPoints() const;
	
	void SetCurrentPoints(const int NewPoints);

	int GetMaxPoints() const;

	void SetMaxPoints(const int NewMax);

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
	int CurrentPoints = 0;

	/**
	 * The maximum number of possible points to put into this Affinity.
	 */
	UPROPERTY(VisibleDefaultsOnly)
	int MaxPoints = 3;
	
};
