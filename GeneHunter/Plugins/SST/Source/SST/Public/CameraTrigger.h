// Copyright 2024 NFB Makes Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraTriggerUpdateContents.h"
#include "GameFramework/Actor.h"
#include "CameraTrigger.generated.h"

struct FCameraTriggerUpdateFloat;
struct FCameraTriggerUpdateBool;
struct FCameraTriggerUpdateVector;

/**
 * A trigger object designed to work with the CameraFollowedCharacter type.
 * Defines regions where the player camera blends to a different camera, and/or
 *   changes parameters (e.g. zoom). Can be configured to revert back to previous
 *   settings when leaving the region.
 */
UCLASS()
class SST_API ACameraTrigger : public AActor
{
	GENERATED_BODY()

	/** If true, the camera will revert to previous settings when leaving the volume */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool UndoAfterEndOverlap;

	/** If not none, will swap to target external camera in the scene */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACameraActor> TargetCamera;

	/** Time over which to smoothly blend to an external camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float TargetCameraBlendTime;

	/** Updates to apply */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<FCameraTriggerUpdateFloat> FloatParameters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<FCameraTriggerUpdateBool> BoolParameters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TArray<FCameraTriggerUpdateVector> VectorParameters;

private:
	class AActor* PreviousCamera;
	TArray<FCameraTriggerUpdateFloat> PreviousFloatParameters;
	TArray<FCameraTriggerUpdateBool> PreviousBoolParameters;
	TArray<FCameraTriggerUpdateVector> PreviousVectorParameters;

public:
	ACameraTrigger();

protected:
	virtual void BeginPlay();

	/** Called when the character enters the trigger volume. */
	UFUNCTION(BlueprintNativeEvent, Category = Camera)
	void OnOverlapBegin(class AActor* ThisActor, class AActor* OtherActor);

	/** Called when the character leaves the trigger volume. */
	UFUNCTION(BlueprintNativeEvent, Category = Camera)
	void OnOverlapEnd(class AActor* ThisActor, class AActor* OtherActor);

	/** Performs the actal modifications to the camera parameters */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Camera)
	void InitiateCameraUpdate(AActor* Actor, bool Undo);

};
