// Copyright 2024 NFB Makes Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSTCharacter.generated.h"

/**
 * Extends the default ACharacter to provide:
 * - A custom character movement component, supporting dash, wallslide, etc.
 * - A FollowCamera component, which follows the character and can be modified via CameraTrigger objects.
 * - Input bindings for left/right motion, Jump, Dash, Crouch, and platform-drop
 * 
 * USSTCharacterMovementComponent should remain the sole authority on movement for this character. 
 */
UCLASS(config=Game)
class SST_API ASSTCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Custom CharacterMovementComponent */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USSTCharacterMovementComponent> SSTCharacterMovementComponent;

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFollowCameraComponent> FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	/** Crouch/Drop Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> CrouchDropAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MouseMoveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;

	/** Time in seconds after dropping through a platform before the button becomes usable for jump input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DropThroughPlatformJumpLockout = .2f;

	/** Show mouse? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bShowMouseCursor = true;

private:
	bool IsJumpStale = false;

public:
	ASSTCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);
	
	/** Called for mouse-triggered movement input */
	void MouseMove(const struct FInputActionValue& Value);

	/** Called for crouch/drop input */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void CrouchDrop();

	/** Called when releasing crouch/drop input */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void StopCrouchDrop();

	/** Called when jump pressed, which could also be a drop-down command */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void JumpOrDrop();

	/** Called for dash input */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void Dash();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE class USSTCharacterMovementComponent* GetSSTCharacterMovement() const { return SSTCharacterMovementComponent; }

	/** Can override in blueprint for custom dash checking on this character */
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Movement")
	bool CanDash() const;

	/** Called when releasing the jump button */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void ReleaseJump();

	/* Overrides to work with custom movement modes */
	virtual bool CanCrouch() const override; 

	virtual void StopJumping() override;

	virtual void ResetJumpState() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void CheckJumpInput(float DeltaTime) override;

	/** Helper -- get collision query params to ignore this actor and its children*/
	virtual FCollisionQueryParams GetIgnoreSelfParams() const;
};

