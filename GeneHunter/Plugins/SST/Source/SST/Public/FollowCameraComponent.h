// Copyright 2024 NFB Makes Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CameraTriggerUpdateContents.h"
#include "FollowCameraComponent.generated.h"

/**
 * A camera component which automatically follows the camera to which it is attached.
 * Designed to work with CameraTrigger, which can adjust this camera when the owning
 *	character enters an overlapping volume. 
 */
UCLASS()
class SST_API UFollowCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

	/** Camera zoom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoomDistance;

	/** The maximum amount by which the camera leads the character, when in follow mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraLeadMaxDistance;

	/** Adjusts the speed with which the camera moves to lead the character, when in follow mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraLeadSpeed;

	/** If true, the camera will stay at max lead distance (plus any offsets) for left/right, regardless of movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool FixLeadAtMax;

	/** If true, locks the camera to a specific z-height, rather than following character as they jump */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool CameraZLock;
	
	/** Z-height of the camera, when CameraZLock == true */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZLockHeight;

	/** Controls speed of blend when swapping to a different camera in the level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraBlendSpeed;

	/** Static offset to add to camera transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FVector CameraLocationOffset = FVector(0.0f, 0.0f, 0.0f);

	/** Static rotation to add to camera (roll, pitch, yaw) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FVector CameraRotationOffset = FVector(0.0f, 0.0f, 0.0f);

	/** If true, camera will freeze its lead position until false (e.g. during dash) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	bool CameraLeadLock;

	/** Set this based on the capsule half-height difference to prevent the camera moving while crouching */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CrouchHeightReduction;

public:
	UFollowCameraComponent();

private:
	class ACharacter* Owner;

	float CurrentLeadOffsetX = 0.0f;
	float CurrentZoomDistance = 0.0f;
	float ZoomDistanceBlendSpeed = 1.0f;
	float CurrentZLockHeight = 0.0f;
	float ZLockHeightBlendSpeed = 1.0f;
	FVector CurrentLocationOffset = FVector(0.0f, 0.0f, 0.0f);
	float LocationOffsetBlendSpeed = 1.0f;
	FVector CurrentRotationOffset = FVector(0.0f, 0.0f, 0.0f);
	float RotationOffsetBlendSpeed = 1.0f;

private:
	void CacheOwner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* These getters return the target value, which may differ from the instantaneous value if it is currently interpolating */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE float GetZoomDistance() const { return CameraZoomDistance; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE float GetMaxLeadDistance() const { return CameraLeadMaxDistance; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE float GetLeadSpeed() const { return CameraLeadSpeed; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE float GetZLockHeight() const { return CameraZLockHeight; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE bool GetZLock() const { return CameraZLock; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE bool GetFixLeadAtMax() const { return FixLeadAtMax; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE FVector GetLocationOffset() const { return CameraLocationOffset; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FORCEINLINE FVector GetRotationOffset() const { return CameraRotationOffset; }

	/* Can be called manually, or overriden in blueprints to define behaviors using different curves */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetZoomDistance(float Value, float BlendTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetMaxLeadDistance(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetLeadSpeed(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetZLockHeight(float Value, float BlendTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetZLock(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetFixLeadAtMax(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetLocationOffset(FVector Value, float BlendTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera")
	void SetRotationOffset(FVector Value, float BlendTime);

	// Setters/getters enabling CameraTrigger objects to update camera parameters without knowing anything about them
	FORCEINLINE float GetDefaultCameraBlendSpeed() const { return CameraBlendSpeed; }
	float UpdateOrGetFloatParameter(ECameraTriggerUpdateFloatParameter Parameter, FCameraTriggerUpdateFloat* Update=nullptr);

	bool UpdateOrGetBoolParameter(ECameraTriggerUpdateBoolParameter Parameter, FCameraTriggerUpdateBool* Update = nullptr);

	FVector UpdateOrGetVectorParameter(ECameraTriggerUpdateVectorParameter Parameter, FCameraTriggerUpdateVector* Update = nullptr);

};
