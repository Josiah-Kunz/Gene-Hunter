#pragma once

#include "CoreMinimal.h"
#include "PermStatMod.h"
#include "PositiveAuraComponent.h"
#include "FullBloom.generated.h"

/**
 * +20% max health
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class POSITIVEAURACOMPONENT_API UFullBloom : public UPositiveAuraComponent
{
	GENERATED_BODY()

	UFullBloom();
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPermStatMod* PermStatMod;
	
	virtual FSupportingText GetSupportingText() override;

	virtual void OnComponentCreated() override;
	
};

