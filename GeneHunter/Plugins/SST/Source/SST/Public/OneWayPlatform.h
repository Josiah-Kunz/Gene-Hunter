// Copyright 2024 NFB Makes Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OneWayPlatform.generated.h"

/**
 * A platform which, by default, allows the character to pass through when jumping up from below, but
 *	becomes solid ground when falling from above. By default, pressing down+jump will cause the character
 *	to fall back through the platform. Both of these capabilities can be disabled per instance. 
 * 
 * Sets collision on a per-character basis, so that in a multiplayer setting one character can remain
 *	standing on the platform while another passes through. 
 */
UCLASS()
class SST_API AOneWayPlatform : public AActor
{
	GENERATED_BODY()

	/** Static Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OneWayPlatform, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	/** Below Trigger Volume -- Disables collision when player approaches from below */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OneWayPlatform, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BelowTrigger;

	/** If true, player can pass through the platform from below (one-way behavior) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OneWayPlatform, meta = (AllowPrivateAccess = "true"))
	bool CanPassThroughFromBelow = true;

	/** If true, the player can drop through the platform while standing on it via an input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OneWayPlatform, meta = (AllowPrivateAccess = "true"))
	bool CanDropDownFromAbove = true;

public:	
	AOneWayPlatform();

protected:
	virtual void BeginPlay() override;

	/** Called when a character approaches the platform from below */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Overlap")
	void OnOverlapBeginBelowTrigger(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Called when a character is no longer directly below the platform */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Overlap")
	void OnOverlapEndBelowTrigger(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/** Call this method with the target character to allow the character to fall through */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RequestCharacterPassthrough(ACharacter* Character);

private:
	/** By default, APawn only exposes per-actor ignore, not per-component. 
	*	We implement functionality as in APawn::MoveIgnoreActorAdd(), but for components.
	*	We implement it here, rather than in a custom character class, to reduce coupling 
	*     and make OneWayPlatform compatible even with applications that use the default ACharacter.
	*/
	void SetCharacterIgnoreComponentWhenMoving(ACharacter* Character, bool bShouldIgnore);
};
