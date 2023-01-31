#pragma once

// Engine
#include "CoreMinimal.h"

// Monster utilities
#include "Affinity.h"
#include "EffectableComponent.h"
#include "UtilityFunctionLibrary.h"

// .gen
#include "AffinitiesComponent.generated.h"

/**
 * A class for storing Types and points, but *not* for calculating Type advantages or doing something with those points.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class AFFINITIESCOMPONENT_API UAffinitiesComponent : public UEffectableComponent
{
#pragma region Standard stuff
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UAffinitiesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

private:
	
	/**
	 * These points can be allocated in-game by the player into affinities. By default, the player has 1 point for any
	 * new Monster so that affinities can be customized from the get-go (so the player has agency which makes for more
	 * exciting gameplay).
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level")
	uint8 UnspentPoints = 1;

public:

	/**
	 * These points can be allocated in-game by the player into affinities. By default, the player has 1 point for any
	 * new Monster so that affinities can be customized from the get-go (so the player has agency which makes for more
	 * exciting gameplay).
	 */
	uint8 GetUnspentPoints();

	/**
	 * These points can be allocated in-game by the player into affinities. By default, the player has 1 point for any
	 * new Monster so that affinities can be customized from the get-go (so the player has agency which makes for more
	 * exciting gameplay).
	 */
	void SetUnspentPoints(uint8 NewPoints);

	/**
	 * These points can be allocated in-game by the player into affinities. By default, the player has 1 point for any
	 * new Monster so that affinities can be customized from the get-go (so the player has agency which makes for more
	 * exciting gameplay).
	 */
	void AddUnspentPoints(const uint8 AddedPoints = 1);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affinities")
	TArray<FAffinity> Affinities;

	/**
	 * Determines if this Monster has any more available Types depending on the current point allocation and
	 * MaxUsableAffinities.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Affinities")
	bool CanChooseNewType();

	/**
	 * Returns the Types that have points allocated in them.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Affinities")
	void GetTypes(TArray<UType*>& Types);
	
	/**
	 * Retrieves the number of Types based on the current point allocation.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Affinities")
	uint8 GetNumTypes();

	/**
	 * Gets the number of Types this Monster may have. For example, if MaxUsableAffinities is 2, this Monster may be
	 * dual-typed.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Affinities")
	uint8 GetMaxUsableAffinities() const;

	/**
	 * Sets the number of Types this Monster may have. For example, if MaxUsableAffinities is 2, this Monster may be
	 * dual-typed.
	 */
	UFUNCTION(BlueprintCallable, Category="Affinities")
	void SetMaxUsableAffinities(const uint8 NewMax);

private:

	/**
	 * The number of Types this Monster may have. For example, if MaxUsableAffinities is 2, this Monster may be
	 * dual-typed.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Affinities")
	uint8 MaxUsableAffinities = 2;
	
	/**
	 * If the actual number of affinities with points exceeds MaxUsableAffinities, these excessive affinities will
	 * have their points stripped. 
	 */
	UFUNCTION(Category="Affinities")
	void ReconcileMax();
	
};
