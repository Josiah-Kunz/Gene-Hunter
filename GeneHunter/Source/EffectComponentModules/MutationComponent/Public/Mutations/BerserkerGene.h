#pragma once

#include "CoreMinimal.h"
#include "MutationComponent.h"
#include "PermStatMod.h"

#include "BerserkerGene.generated.h"

/**
 * +15% PhA | -10% PhD, SpD
 * A little boring, but sometimes it's best to have at least one boring, tried-and-true option.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class MUTATIONCOMPONENT_API UBerserkerGene : public UMutationComponent
{
	GENERATED_BODY()

	UBerserkerGene();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPermStatMod* PermStatMod;
	
	virtual FSupportingText GetSupportingText() override;

	virtual void OnComponentCreated() override;
	
};

