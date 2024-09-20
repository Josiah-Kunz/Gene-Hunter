#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverlapTracker.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNCHARACTER_API UOverlapTracker : public UActorComponent
{
	GENERATED_BODY()

public:
	UOverlapTracker();

	/**
	 * Let's say you want to also track overlapping UCombatStatsComponents. You would make sure this array contains
	 * "UCombatStatsComponent".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overlap")
	TArray<TSubclassOf<UActorComponent>> TrackedComponents;
	
	UFUNCTION(BlueprintCallable, Category="Overlap")
	const TArray<AActor*>& GetOverlappingActors() const;

	UFUNCTION(BlueprintCallable, Category="Overlap")
	void GetOverlappingComponents(const TSubclassOf<UActorComponent> ComponentType, TArray<UActorComponent*>& Components);

	// User-selectable collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	UShapeComponent* CollisionComponent;

protected:
	
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

#if WITH_EDITOR
	// To respond to property changes in the editor (like changing the CollisionComponent)
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
