#pragma once

#include "EffectComponent.h"

#include "DependentEffectComponent.generated.h"

/**
 * TODO
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDependentEffectComponent : public UEffectComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEffectComponent* Owner;

public:

	virtual void SetOwner(UEffectComponent* NewOwner);

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual int32 GetStacks() override;
	
	/*
	virtual void OnRefreshStacks() override;

	virtual void OnReduceStacks() override;
	
	virtual void Silence() override;

	virtual void Unsilence() override;

	virtual bool ShouldApplyEffect() override;
	*/
	
	/**
	 * Always false.
	 */
	virtual bool IsVisibleToUI() const override;
	
};
