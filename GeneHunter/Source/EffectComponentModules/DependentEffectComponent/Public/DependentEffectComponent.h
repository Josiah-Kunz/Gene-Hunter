#pragma once

#include "EffectComponent.h"
#include "Outlets/OnRemoveEffectOutlet.h"

#include "DependentEffectComponent.generated.h"

/**
 * Adds common, cross-class functionality to other effects. This is like multiple inheritance (but that's not allowed
 * in Unreal). See documentation (e.g., utility-tables.pdf).
 *
 * Examples that might inherit from this:
 *	- A Buff that increases HP by 20%
 *	- A Debuff that reduces PhA by 10%
 *	- A Mutation that increases Crt by 5%
 *
 * Critical functionality:
 *	- When inheriting, make sure ApplyEffect and RemoveEffect do something.
 *	- On the Owner's OnComponentCreated, use:
 *		- ADD_COMPONENT(UDependentEffectComponent, Dependent, GetOwner())
 *		- Dependent->SetOwner(this);
 *		- # Do some customization here, such as setting Dependent variables
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class DEPENDENTEFFECTCOMPONENT_API UDependentEffectComponent : public UEffectComponent
{
	GENERATED_BODY()

#pragma region Variables
	
private:

	UPROPERTY()
	UEffectComponent* Owner;

	UPROPERTY()
	bool bDeactivated;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bHasOwner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bApplied;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBeforeOnRemoveEffectDelegate OnRemoveDelegate;

#pragma endregion

#pragma region Novel functions

private:

	UFUNCTION()
	void CallRemoveEffect(const UEffectComponent* EffectToRemove);
	
public:

	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	virtual void SetOwner(UEffectComponent* NewOwner);

#pragma endregion

#pragma region Adding and removing

public:

	virtual void ApplyEffect() override;

	virtual void RemoveEffect() override;



#pragma endregion

#pragma region Mimicing Owner

public:

	virtual float GetPriority() override;
	
	virtual int32 GetStacks() override;

	virtual int32 MaxStacks() override;

	virtual bool ShouldApplyEffect() override;
	
	/**
	 * Always false.
	 */
	virtual bool IsVisibleToUI() const override;

#pragma endregion
	
};
