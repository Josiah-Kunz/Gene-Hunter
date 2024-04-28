// Copyright 2024 NFB Makes Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SSTCharacterMovementComponent.generated.h"

/**
 * Overrides the default CharacterMovementComponent to provide custom movement:
 *   - Wallsliding
 *   - Walljumping
 *   - Dashing
 *	 - Drop down through a OneWayPlatform
 *
 * Also enables 180-degree only left/right smooth rotation with configurable rate.
 *
 * These features are designed for replication to support network play.
 */

 // Exact dashing behavior can be designed in blueprints via delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPerformDashDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDashDelegate);

// Custom character movement modes
UENUM(BlueprintType)
enum ESSTCharacterMovementMode
{
	FSSTMOVE_NONE UMETA(Hidden),
	FSSTMOVE_WALLSLIDING   UMETA(DisplayName = "Wallsliding"),
	FSSTMOVE_DASHING	UMETA(DisplayName = "Dashing"),
	FSSTMOVE_MAX      UMETA(Hidden)
};

UCLASS()
class SST_API USSTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

		/* SavedMove class for replicating state data */
		class FSavedMove_SSTCharacter : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		bool SavedFacingRight;
		bool SavedWantsToDash;
		bool SavedWantsToPlatformDrop;

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	/* Override NetworkPredictionData to use our custom SavedMove class */
	class FNetworkPredictionData_Client_SSTCharacter : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_SSTCharacter(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

protected:
	USSTCharacterMovementComponent();

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	/** Owning character for this component */
	UPROPERTY(Transient)
	TObjectPtr<class ASSTCharacter> SSTCharacterOwner;

	/** Time it takes to fully turn around, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float TurnAroundSeconds = 0.12f;

	// Wallslide parameters
	/** Determines whether the character is capable of wallsliding. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool CanWallSlide = true;

	/** Speed at which the character slides down a wall */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideSpeed = 200.0f;

	/** (0-1) Controls how strictly along the x-axis the player must hold an analog input to continue wallsliding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideInputAngleStrictness = 0.2f;

	/** (0-1) Lower values allow a wall greater deviations from pure vertical before it is no longer eligible for wallslide */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideAllowableWallAngleStrictness = .8f;

	/** In units, the distance from the wall at which the character slides */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideDistanceFromWall = 5.0f;

	/** In units, the distance above the floor before landing and ending the wallslide */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideMinFloorHeight = 5.0f;

	/** The force with which the character jumps out of a wallslide. Set to 0 to disable walljump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideJumpOffForce = 1400.0f;

	/** The angle with which the character jumps out of a wallslide. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideJumpAngle = 45.0f;

	/** Time after performing a walljump before the jump button can be used to double-jump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideJumpInputDisableSeconds = 0.2f;

	/** Buffer after releasing a wallslide and beginning falling during which a jump will still count as a walljump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WallslideReleaseWalljumpBufferSeconds = 0.2f;

	/** Minimum amount of time between walljumps. Should be larger than WallslideReleaseWalljumpBufferSeconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WalljumpCooldownSeconds = 0.5f;

	/** If false, dashing is disabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool DashEnabled = true;

	/** Number of dashes a character can perform in midair before landing. No limit if negative. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	int MaxDashesBeforeLanding = 1;

	/** In units, length of a dash. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float DashDistance = 2000;

	/** In seconds, duration of a dash. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float DashDurationSeconds = .2;

	/** Cooldown between dashes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float DashCooldownSeconds = .7;

	/** Friction applied during dashes. Can be modified via blueprint e.g. if in water.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float DashFriction = 0.0f;

	/** If true, the player can turn around while in the middle of a dash (changing direction of dash) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool CanTurnWhileDashing = false;

	/** If true, the player can jump while in the middle of a dash, immediately ending it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool CanJumpCancelDash = true;

	/** When dashing on a slope facing downwards, the character will go down the slope if true, or horizontally outward if false.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool DashFollowsDownwardSlopes = true;

public:
	/** If true, attempt to dash on next update. */
	UPROPERTY(Category = Movement, VisibleInstanceOnly, BlueprintReadOnly)
	bool WantsToDash = false;

	/** Set by character movement to specify that this Character is currently dashing. */
	UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_IsDashing, Category = Character)
	uint32 IsDashing : 1;

	/** Blueprint-assignable dash implementation */
	UPROPERTY(BlueprintAssignable)
	FPerformDashDelegate PerformDashDelegate;
	UPROPERTY(BlueprintAssignable)
	FEndDashDelegate EndDashDelegate;

	/** Set by character movement to specify that this Character is currently wallsliding. */
	UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_IsWallsliding, Category = Character)
	uint32 IsWallsliding : 1;

	/** If true, attempt to drop through platform on next update. */
	UPROPERTY(Category = Movement, VisibleInstanceOnly, BlueprintReadOnly)
	bool WantsToPlatformDrop = false;

private:
	UPROPERTY(replicated)
	bool FacingRight;

	bool MoveInputsEnabled = true;
	bool Turning = false;

	bool HasRecentlyWallSlid = false;
	bool HasRecentlyWalljumped = false;
	float LastWallJumpTime = 0;
	float LastWallslideFallingReleaseTime = 0;
	bool LastWallWasRelativeRight;

	uint8 CurrentDashesBeforeLanding = 0;
	float LastDashTime = 0;

	float LastDropThroughPlatformTime = 0.0f;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode);

	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

	virtual void StartNewPhysics(float deltaTime, int32 Iterations) override;

	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;

	virtual float GetMaxSpeed() const override;

	virtual float GetMaxBrakingDeceleration() const override;

	virtual bool CanAttemptJump() const override;

	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;

private:
	/** Begin wallslide */
	void EnterWallslide();

	/** Finish wallslide */
	void ExitWallslide();

	/** Apply physics for wallslide */
	void PhysWallslide(float DeltaTime, int32 Iterations);

	/** Trace to find wall hits */
	bool GetWallslideWall(TArray<FHitResult>& Hits) const;

	/** Trace to find floor hits */
	bool GetWallslideFloor(TArray<FHitResult>& Hits) const;

	/** Check whether a candidate wall object is greater than our capsule height */
	bool CheckWallAtLeastCapsuleHeight(const FHitResult& Hit);

	/** Verify whether a given wallslide trace result is appropriate for wallsliding */
	bool IsEligibleWallForSliding(FHitResult& Hit);

	/** Returns whether the player is holding in the direction they are facing */
	bool IsHeadedForwards() const;

	/** Helper function to check whether a wallslide is occurring just above valid floor */
	bool GetValidFloorBeneath(FHitResult& Hit);

	/** Performs wall jump */
	void PerformWallJump();

	/** Begin dash */
	void EnterDash();

	/** Finish dash */
	void ExitDash(bool DashCancelled = false);

	/** Apply physics for dash */
	void PhysDash(float DeltaTime, int32 Iterations);

	/** Performs the dash */
	void PerformDash();

	/** Determines whether the player is standing on a OneWayPlatform */
	class AOneWayPlatform* FindOneWayPlatform();

public:
	/** Overrides to enable custom movement modes */
	virtual void AddInputVector(FVector WorldVector, bool bForce = false) override;

	virtual bool DoJump(bool bReplayingMoves) override;

	virtual bool CanCrouchInCurrentState() const override;

	/** Whether the character is currently facing right (or has started turning towards it) */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	FORCEINLINE bool IsFacingRight() const { return FacingRight; }

	/** To be called by owning character, upon BeginPlay() */
	void SetFacingRight(bool bFacingRight);

	/** Checks whether the character is currently in the specified custom movement mode */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	bool IsCustomMovementMode(ESSTCharacterMovementMode Mode) const;

	/** Whether the character is wallsliding, or has just left a wall, and can walljump */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	bool CanWalljump() const;

	/** Begins a 180-degree turn. Returns false if the character is already in a turn */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool RequestTurnAround();

	/** Called when beginning a wallslide. Can be extended via blueprint */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void OnBeginWallslide();

	/** Called when finishing a wallslide. Can be extended via blueprint */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void OnEndWallslide();

	/** Returns true if the character is currently able to dash */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	bool CanDash() const;

	/** Called when beginning a dash. Can be extended via blueprint */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void OnBeginDash();

	/** Called when finishing a dash. Can be extended via blueprint */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	void OnEndDash();

	/** Returns the last time the owning character dropped through a OneWayPlatform */
	FORCEINLINE float GetLastDropThroughPlatformTime() const { return LastDropThroughPlatformTime; }

	/** Handle Wallsliding replicated from server */
	UFUNCTION()
	virtual void OnRep_IsWallsliding();

	/** Handle Dashing replicated from server */
	UFUNCTION()
	virtual void OnRep_IsDashing();
};
