#pragma once

// Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Affinities
#include "Affinity.h"

// .gen
#include "AffinitiesComponent.generated.h"

UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class AFFINITIESCOMPONENT_API UAffinitiesComponent : public UActorComponent
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affinities")
	TArray<FAffinity> Affinities;
	
};
