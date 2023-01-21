#pragma once

#include "EffectDelegate.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FEffectDelegate
{
	GENERATED_BODY()

public:
	virtual ~FEffectDelegate() = default;

	/**
	 * The lower the priority, the farther away it is from execution. If two priorities are tied, the execution order is
	 * randomized. Order is set externally by EffectsComponent. Order:
	 *
	 *		-	Intrinsic delegates (no Effect attached)
	 *		-	"Before" delegates
	 *			-	Priority 1
	 *			-	Priority 2
	 *			-	...
	 *		-	[Function executes]
	 *		-	"After" delegates
	 *			-	...
	 *			-	Priority 2
	 *			-	Priority 1
	 *		-	Intrinsic delegates
	 * 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Priority = 50;

	
};
