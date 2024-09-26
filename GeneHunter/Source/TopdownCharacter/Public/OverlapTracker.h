#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "OverlapTracker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FBeginOverlapEvent,
	UPrimitiveComponent*, OverlappedComp,
	AActor*, OtherActor, 
	UPrimitiveComponent*, OtherComp,
	int32, OtherBodyIndex, 
	bool, bFromSweep,
	const FHitResult&, SweepResult
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FEndOverlapEvent,
	UPrimitiveComponent*, OverlappedComp,
	AActor*, OtherActor, 
	UPrimitiveComponent*, OtherComp,
	int32, OtherBodyIndex
);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNCHARACTER_API UOverlapTracker : public USceneComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="Events")
	FBeginOverlapEvent BeginOverlap;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FEndOverlapEvent EndOverlap;

	/**
	 * Let's say you want to also track overlapping UCombatStatsComponents. You would make sure this array contains
	 * "UCombatStatsComponent".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overlap")
	TArray<TSubclassOf<UActorComponent>> TrackedComponents = {UCombatStatsComponent::StaticClass()};
	
	UOverlapTracker();
	
	UFUNCTION(BlueprintCallable, Category="Overlap")
	const TArray<AActor*>& GetOverlappingActors() const;

	UFUNCTION(BlueprintCallable, Category="Overlap")
	void GetOverlappingComponents(const TSubclassOf<UActorComponent> ComponentType, TArray<UActorComponent*>& Components);
	
	UFUNCTION(BlueprintCallable, Category="Overlap")
	void SetCollisionComponent(UShapeComponent* NewCollider);

	UFUNCTION(BlueprintCallable, Category="Overlap")
	void SetCollisionLocation(const FVector WorldLocation);
	
protected:

	/**
	 * This can be assigned in the Blueprint. If it's not part of the RootComponent, it won't follow the Actor around.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	UShapeComponent* CollisionComponent;
	
	// Array to hold actors currently overlapping
	UPROPERTY(VisibleAnywhere, Category = "Overlap")
	TArray<AActor*> OverlappingActors;
	
	/**
	 * Collection of instances tracked by TrackedComponents.
	 */
	TMap<TSubclassOf<UActorComponent>, TArray<UActorComponent*>> TrackedComponentInstances;
	
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;


	// Callback for when an overlap begins
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

	// Callback for when an overlap ends
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to bind overlap events
	void BindOverlapEvents();
    
	// Function to unbind overlap events
	void UnbindOverlapEvents() const;

};
