#pragma once

#include "CoreMinimal.h"
#include "ActorSpawnScheme.h"
#include "EffectableComponent.h"
#include "GetExpirationDistanceOutlet.h"
#include "GetExpirationTimeOutlet.h"
#include "ExpirationComponent.generated.h"

/**
 * Put this on an Actor to have them expire (delete themselves) eventually!
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UExpirationComponent : public UEffectableComponent
{
	GENERATED_BODY()

public:
	
	/**
	 * Before parameters:
	 *  - [const float] The original, unmodified distance before the Actor expires (as set by the user in the editor).
	 *  - [float&] The current value of the expiration distance.
	 *
	 *  After parameters:
	 *  - [const float]
	 *  - [const float]
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetExpirationDistanceOutlet GetExpirationDistanceOutlet;

	/**
	 * Before parameters:
	 *  - [const float] The original, unmodified time before the Actor expires (as set by the user in the editor).
	 *  - [float&] The current value of the expiration time.
	 *
	 *  After parameters:
	 *  - [const float]
	 *  - [const float]
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetExpirationTimeOutlet GetExpirationTimeOutlet;

	/**
	 * The Actor will expire after it travels this distance. Set negative to disable.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Expiration")
	float Distance = -1;
	
	/**
	 * The Actor will expire after this many seconds. Set negative to disable.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Expiration")
	float Seconds = -1;
	
	/**
	 * Possible Actors to spawn when expiring.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Expiration")
	TArray<TSubclassOf<UActorSpawnScheme>> SpawnOnExpire;

	/**
	 * Re-registers the owning Actor, sets the current distance to zero, and sets the current time to zero.
	 * This is done automatically in BeginPlay.
	 */
	UFUNCTION(BlueprintCallable)
	void Reset();
	
	UExpirationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	AActor* Actor;
	
	UPROPERTY()
	FVector OGLocation;

	UPROPERTY()
	float CurrentTime;

	UPROPERTY()
	TArray<UActorSpawnScheme*> SpawnOnExpireInstances;
	
	virtual void BeginPlay() override;

	float GetExpirationDistance();
	
	float GetExpirationTime();

	void Expire();
	
};
