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

	/**
	 * The maximum number of possible points to put into this Affinity.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	int MaxPoints = 3;

	/**
	 * The current number of points put into this Affinity.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	int CurrentPoints = 0;

private:

	bool bLocked = false;
	
};
