// Copyright 2024 NFB Makes Games. All Rights Reserved.


#include "SSTCharacterMovementComponent.h"
#include "SSTCharacter.h"
#include "Components/CapsuleComponent.h"
#include "OneWayPlatform.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"

/*
* FSavedMove_SSTCharacter
*/
bool USSTCharacterMovementComponent::FSavedMove_SSTCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_SSTCharacter* NewSSTMove = static_cast<FSavedMove_SSTCharacter*>(NewMove.Get());

	if (SavedFacingRight != NewSSTMove->SavedFacingRight) { return false; }
	if (SavedWantsToDash != NewSSTMove->SavedWantsToDash) { return false; }
	if (SavedWantsToPlatformDrop != NewSSTMove->SavedWantsToPlatformDrop) { return false; }

	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void USSTCharacterMovementComponent::FSavedMove_SSTCharacter::Clear()
{
	FSavedMove_Character::Clear();

	SavedFacingRight = true;
	SavedWantsToDash = false;
	SavedWantsToPlatformDrop = false;
}

uint8 USSTCharacterMovementComponent::FSavedMove_SSTCharacter::GetCompressedFlags() const
{
	uint8 Result = FSavedMove_Character::GetCompressedFlags();

	/* Flags used:
	* Custom_0: FacingRight (Used for syncing ongoing 180 smooth rotation)
	* Custom_1: Dash
	* Custom_2: PlatformDrop
	*/
	if (SavedFacingRight)
	{
		Result |= FLAG_Custom_0;
	}
	if (SavedWantsToDash)
	{
		Result |= FLAG_Custom_1;
	}
	if (SavedWantsToPlatformDrop)
	{
		Result |= FLAG_Custom_2;
	}

	return Result;
}

void USSTCharacterMovementComponent::FSavedMove_SSTCharacter::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	USSTCharacterMovementComponent* SSTCharacterMovement = Cast<USSTCharacterMovementComponent>(C->GetCharacterMovement());

	SavedFacingRight = SSTCharacterMovement->FacingRight;
	SavedWantsToDash = SSTCharacterMovement->WantsToDash;
	SavedWantsToPlatformDrop = SSTCharacterMovement->WantsToPlatformDrop;
}

void USSTCharacterMovementComponent::FSavedMove_SSTCharacter::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);

	USSTCharacterMovementComponent* SSTCharacterMovement = Cast<USSTCharacterMovementComponent>(C->GetCharacterMovement());

	SSTCharacterMovement->FacingRight = SavedFacingRight;
	SSTCharacterMovement->WantsToDash = SavedWantsToDash;
	SSTCharacterMovement->WantsToPlatformDrop = SavedWantsToPlatformDrop;
}

/*
* FNetworkPredictionData_Client_SSTCharacter
*/
USSTCharacterMovementComponent::FNetworkPredictionData_Client_SSTCharacter::FNetworkPredictionData_Client_SSTCharacter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr USSTCharacterMovementComponent::FNetworkPredictionData_Client_SSTCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_SSTCharacter);
}

/*
* USSTCharacterMovementComponent
*/
FNetworkPredictionData_Client* USSTCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		USSTCharacterMovementComponent* MutableThis = const_cast<USSTCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_SSTCharacter(*this);
	}
	return ClientPredictionData;
}

USSTCharacterMovementComponent::USSTCharacterMovementComponent()
{
	SetIsReplicatedByDefault(true);
}

void USSTCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	FacingRight = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	WantsToDash = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
	WantsToPlatformDrop = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}

void USSTCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USSTCharacterMovementComponent, FacingRight, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(USSTCharacterMovementComponent, IsWallsliding, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(USSTCharacterMovementComponent, IsDashing, COND_SimulatedOnly);
}

void USSTCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SSTCharacterOwner = Cast<ASSTCharacter>(GetOwner());
}

void USSTCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if (!SSTCharacterOwner) { return; }
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		if (IsDashing)
		{
			if (MovementMode != MOVE_Custom || CustomMovementMode != FSSTMOVE_DASHING)
			{
				IsDashing = false;
			}
		}

		if (IsWallsliding)
		{
			// Wallsliding is "buffered" when dashing into a wall, while waiting for dash to complete
			if (MovementMode != MOVE_Custom || (CustomMovementMode != FSSTMOVE_WALLSLIDING && CustomMovementMode != FSSTMOVE_DASHING))
			{
				IsWallsliding = false;
			}
		}
	}
	
}

void USSTCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
	
	// Check for platform drop
	if (WantsToPlatformDrop)
	{
		WantsToPlatformDrop = false;
		AOneWayPlatform* platform = FindOneWayPlatform();
		if (platform)
		{
			platform->RequestCharacterPassthrough(SSTCharacterOwner);
			LastDropThroughPlatformTime = GetWorld()->GetTimeSeconds();
			UnCrouch();
		}
	}

	// Check for end dash
	if (IsDashing && GetWorld()->GetTimeSeconds() - LastDashTime >= DashDurationSeconds)
	{
		ExitDash();
	}

	// Check for dash
	if (WantsToDash)
	{
		if (CanDash())
		{
			EnterDash();
		}
	}
	WantsToDash = false;

	// Check if we can re-enable jumping after a walljump
	if (HasRecentlyWalljumped)
	{
		if (GetWorld()->GetTimeSeconds() > LastWallJumpTime + WallslideJumpInputDisableSeconds)
		{
			HasRecentlyWalljumped = false;
		}
	}

	// Check if the buffer to convert a jump into a walljump has passed
	if (HasRecentlyWallSlid)
	{
		if (GetWorld()->GetTimeSeconds() > LastWallslideFallingReleaseTime + WallslideReleaseWalljumpBufferSeconds)
		{
			HasRecentlyWallSlid = false;
		}
	}

	// Check for wallslide
	// If we are in the air and holding in our forward direction, with negative z velocity
	if (IsFalling() && IsHeadedForwards() && !IsDashing && Velocity.Z <= 0)
	{
		// Check for a wall in front and no floor beneath
		FHitResult Floor;
		if (!GetValidFloorBeneath(Floor))
		{
			TArray<FHitResult> HitResultsWall;
			GetWallslideWall(HitResultsWall);
			for (FHitResult Hit : HitResultsWall)
			{
				if (IsEligibleWallForSliding(Hit))
				{
					EnterWallslide();
				}
			}
		}
	}
}

void USSTCharacterMovementComponent::StartNewPhysics(float deltaTime, int32 Iterations)
{
	/*
	* Apply ongoing rotation if we are in the middle of turn
	* This allows us to finish a turn once we've tapped in the opposite direction
	*  even if the player releases before finishing a full turn.
	* However, we still allow the user to add linear velocity as normal, as the 
	* alternative (rejected inputs until the turn is completed) feels sluggish.
	* OrientRotationToMovement and UseControllerDesiredRotation should remain off
	*  unless the desired behavior is for players to turn around faster when holding
	*  in the opposite direction.
	*/
	FVector forward = SSTCharacterOwner->GetActorForwardVector();
	if ((FacingRight && (forward.X < 1.f - FLT_EPSILON))
		|| (!FacingRight && (forward.X > -1.f + FLT_EPSILON)))
	{
		float angleFromXAxis = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(forward, (FacingRight ? 1 : -1) * FVector::ForwardVector)));

		FRotator RotationToAdd(0, FMath::Clamp((FacingRight ? -1 : 1) * deltaTime * 180 / TurnAroundSeconds, -angleFromXAxis, angleFromXAxis), 0);

		FHitResult Hit(1.0f);
		SafeMoveUpdatedComponent(FVector::ZeroVector, UpdatedComponent->GetComponentQuat() * RotationToAdd.Quaternion(), false, Hit);
	}
	else // finished turning
	{
		Turning = false;
	}

	Super::StartNewPhysics(deltaTime, Iterations);
}

void USSTCharacterMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	Super::PhysCustom(DeltaTime, Iterations);

	switch (CustomMovementMode)
	{
	case FSSTMOVE_WALLSLIDING:
		PhysWallslide(DeltaTime, Iterations);
		break;
	case FSSTMOVE_DASHING:
		PhysDash(DeltaTime, Iterations);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Unrecognized custom movement mode"))
	}
}

float USSTCharacterMovementComponent::GetMaxSpeed() const
{
	if (MovementMode != MOVE_Custom) { return Super::GetMaxSpeed(); }

	switch (CustomMovementMode)
	{
	case FSSTMOVE_WALLSLIDING:
		return WallslideSpeed;
	case FSSTMOVE_DASHING:
		return DashDistance / DashDurationSeconds;
	default:
		UE_LOG(LogTemp, Error, TEXT("Attempt to get max speed with an unknown movement mode"))
			return 0.0f;
	}
}

float USSTCharacterMovementComponent::GetMaxBrakingDeceleration() const
{
	if (MovementMode != MOVE_Custom) { return Super::GetMaxSpeed(); }

	switch (CustomMovementMode)
	{
	case FSSTMOVE_WALLSLIDING:
		return 0.0f;
	case FSSTMOVE_DASHING:
		return 0.0f;
	default:
		UE_LOG(LogTemp, Error, TEXT("Attempt to get max braking deceleration with an unknown movement mode"))
			return 0.0f;
	}
}

bool USSTCharacterMovementComponent::CanAttemptJump() const
{
	return Super::CanAttemptJump() || CanWalljump() || (CanJumpCancelDash && IsDashing);
}

void USSTCharacterMovementComponent::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	Super::ProcessLanded(Hit, remainingTime, Iterations);

	CurrentDashesBeforeLanding = 0;
}

void USSTCharacterMovementComponent::EnterWallslide()
{
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		IsWallsliding = true;
	}

	SetMovementMode(MOVE_Custom, ESSTCharacterMovementMode::FSSTMOVE_WALLSLIDING);
	LastWallWasRelativeRight = FacingRight;
	OnBeginWallslide();
}

void USSTCharacterMovementComponent::ExitWallslide()
{
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		IsWallsliding = false;
	}

	FHitResult Floor;
	if (GetValidFloorBeneath(Floor)) // land
	{
		if (CharacterOwner)
		{
			CharacterOwner->Landed(Floor);
		}
		CurrentDashesBeforeLanding = 0;
		SetMovementMode(MOVE_Walking);
	}
	else // fall
	{
		SetMovementMode(MOVE_Falling);
		HasRecentlyWallSlid = true;
		LastWallslideFallingReleaseTime = GetWorld()->GetTimeSeconds();
	}
	OnEndWallslide();
}

void USSTCharacterMovementComponent::PhysWallslide(float DeltaTime, int32 Iterations)
{
	if (DeltaTime < MIN_TICK_TIME) { return; }

	// During wallslide we intentionally:
	// - Do not call CalcVelocity
	// - Disregard leftover root motion
	// 
	// End the wallslide if: we land, user input stops, we lose our ability to wallslide, or we are no longer against a wall
	// Simulated proxies should not manually end their own wallslide state
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		bool FinishWallslide = false;
		TArray<FHitResult> HitResultsWall;
		FHitResult Floor;
		if (!IsHeadedForwards()
			|| !CanWallSlide
			|| GetValidFloorBeneath(Floor)
			|| !GetWallslideWall(HitResultsWall))
		{
			FinishWallslide = true;
		}

		bool SuitableWall = false;
		for (FHitResult Hit : HitResultsWall)
		{
			if (IsEligibleWallForSliding(Hit))
			{
				SuitableWall = true;
				break;
			}
		}
		if (FinishWallslide || !SuitableWall)
		{
			ExitWallslide();
			StartNewPhysics(DeltaTime, Iterations);
			return;
		}
	}

	// No acceleration during a wallslide
	Velocity = WallslideSpeed * FVector::DownVector;
	Acceleration = FVector::ZeroVector;

	Iterations++;
	bJustTeleported = false;

	FVector InitialLocation = UpdatedComponent->GetComponentLocation();
	FQuat InitialRotation = UpdatedComponent->GetComponentQuat();
	FVector LocationUpdate = Velocity * DeltaTime;
	FHitResult Hit(1.0f);
	SafeMoveUpdatedComponent(LocationUpdate, InitialRotation, true, Hit);

	if (Hit.Time < 1.0f)
	{
		HandleImpact(Hit, DeltaTime, LocationUpdate);
		Velocity = (UpdatedComponent->GetComponentLocation() - InitialLocation) / DeltaTime;
	}
}

bool USSTCharacterMovementComponent::GetWallslideWall(TArray<FHitResult>& Hits) const
{
	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start + ((SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() + WallslideDistanceFromWall) * SSTCharacterOwner->GetActorForwardVector());
	return GetWorld()->LineTraceMultiByProfile(Hits, Start, End, TEXT("BlockAll"), SSTCharacterOwner->GetIgnoreSelfParams());
}

bool USSTCharacterMovementComponent::GetWallslideFloor(TArray<FHitResult>& Hits) const
{
	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start + (FVector::DownVector * (SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + WallslideMinFloorHeight));
	return GetWorld()->LineTraceMultiByProfile(Hits, Start, End, TEXT("BlockAll"), SSTCharacterOwner->GetIgnoreSelfParams());
}

bool USSTCharacterMovementComponent::CheckWallAtLeastCapsuleHeight(const FHitResult& Hit)
{
	TArray<FHitResult> TopHits;
	TArray<FHitResult> BottomHits;
	AActor* HitActor = Hit.GetActor();

	// Check top
	FVector Start = UpdatedComponent->GetComponentLocation() + (FVector::UpVector * SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FVector End = Start + (SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2 * SSTCharacterOwner->GetActorForwardVector());
	if (!GetWorld()->LineTraceMultiByProfile(TopHits, Start, End, TEXT("BlockAll"), SSTCharacterOwner->GetIgnoreSelfParams()))
	{
		return false;
	}
	bool FoundSameObject = false;
	for (const FHitResult& TopHit : TopHits)
	{
		if (TopHit.GetActor() == HitActor)
		{
			FoundSameObject = true;
			break;
		}
	}
	if (!FoundSameObject) { return false; }

	// Check bottom
	Start = UpdatedComponent->GetComponentLocation() + (FVector::DownVector * SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	End = Start + (SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2 * SSTCharacterOwner->GetActorForwardVector());
	if (!GetWorld()->LineTraceMultiByProfile(BottomHits, Start, End, TEXT("BlockAll"), SSTCharacterOwner->GetIgnoreSelfParams()))
	{
		return false;
	}
	FoundSameObject = false;
	for (const FHitResult& BottomHit : BottomHits)
	{
		if (BottomHit.GetActor() == HitActor)
		{
			FoundSameObject = true;
			break;
		}
	}
	if (!FoundSameObject) { return false; }

	return true;
}

bool USSTCharacterMovementComponent::IsEligibleWallForSliding(FHitResult& Hit)
{
	// Check whether wall angle is within our allowable range
	if (FVector::DotProduct(Hit.Normal, -1 * SSTCharacterOwner->GetActorForwardVector()) < WallslideAllowableWallAngleStrictness)
	{
		return false;
	}

	// Check whether wall is suitably long (e.g. ignore small platforms)
	if (!CheckWallAtLeastCapsuleHeight(Hit))
	{ 
		return false; 
	}

	return true;
}

bool USSTCharacterMovementComponent::IsHeadedForwards() const
{
	return FVector::DotProduct(SSTCharacterOwner->GetActorForwardVector(), Acceleration.GetSafeNormal()) >= WallslideInputAngleStrictness;
}

bool USSTCharacterMovementComponent::GetValidFloorBeneath(FHitResult& Hit)
{
	TArray<FHitResult> HitResultsFloor;
	if (GetWallslideFloor(HitResultsFloor))
	{
		for (FHitResult hit : HitResultsFloor)
		{
			// Bit of a hack: We are reusing the IsValidLandingSpot logic, but this method expects to be called 
			//  after an attempted movement of the component into the floor. We are calling from a trace,  
			//  so we need to adjust the effective hit impact
			hit.ImpactPoint.Z -= SSTCharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			if (IsValidLandingSpot(UpdatedComponent->GetComponentLocation(), hit))
			{
				Hit = hit;
				return true;
			}
		}
	}
	return false;
}

void USSTCharacterMovementComponent::PerformWallJump()
{
	LastWallJumpTime = GetWorld()->GetTimeSeconds();
	HasRecentlyWalljumped = true;
	SSTCharacterOwner->JumpCurrentCount--; // walljump does not count against jump count

	if (FacingRight == LastWallWasRelativeRight)
	{
		RequestTurnAround();
	}
	FVector LaunchVector = WallslideJumpOffForce * FVector::ForwardVector;
	FRotator LaunchRotator(FacingRight ? WallslideJumpAngle : WallslideJumpAngle + 90.0f, 0.0f, 0.0f);
	Launch(LaunchRotator.RotateVector(LaunchVector));

}

void USSTCharacterMovementComponent::EnterDash()
{
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		IsDashing = true;
	}

	// If we're midair, update current midair dash count
	if (IsFalling() || IsWallsliding)
	{
		CurrentDashesBeforeLanding++;
	}
	SetMovementMode(MOVE_Custom, ESSTCharacterMovementMode::FSSTMOVE_DASHING);
	LastDashTime = GetWorld()->GetTimeSeconds();
	PerformDash();
	OnBeginDash();
}

void USSTCharacterMovementComponent::ExitDash(bool DashCancelled /* = false */)
{
	if (SSTCharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		IsDashing = false;
	}

	FHitResult Floor;
	if (GetValidFloorBeneath(Floor) && !DashCancelled) // land
	{
		SetMovementMode(MOVE_Walking);
	}
	else // fall
	{
		SetMovementMode(MOVE_Falling);
	}
	EndDashDelegate.Broadcast();
	OnEndDash();
}

void USSTCharacterMovementComponent::PhysDash(float DeltaTime, int32 Iterations)
{
	if (DeltaTime < MIN_TICK_TIME) { return; }

	RestorePreAdditiveRootMotionVelocity();

	/** Allow the blueprint delegate to handle the actual physics of the dash by setting velocity, gravity, etc. */

	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		CalcVelocity(DeltaTime, DashFriction, true, GetMaxBrakingDeceleration());
	}
	ApplyRootMotionToVelocity(DeltaTime);

	Iterations++;
	bJustTeleported = false;
	
	FindFloor(UpdatedComponent->GetComponentLocation(), CurrentFloor, false);
	if (CurrentFloor.IsWalkableFloor() 
		&& (DashFollowsDownwardSlopes || CurrentFloor.HitResult.ImpactNormal.X * Velocity.X < 0)) 
	{
		// if on ground, need to compensate for any slope
		FStepDownResult StepDownResult;
		MoveAlongFloor(Velocity, DeltaTime, &StepDownResult);
	}
	else // midair, or we are configured to not follow the slope
	{
		FVector InitialLocation = UpdatedComponent->GetComponentLocation();
		FQuat InitialRotation = UpdatedComponent->GetComponentQuat();
		FVector LocationUpdate = Velocity * DeltaTime;
		FHitResult Hit(1.0f);

		SafeMoveUpdatedComponent(LocationUpdate, InitialRotation, true, Hit);
		if (Hit.Time < 1.0f)
		{
			HandleImpact(Hit, DeltaTime, LocationUpdate);
			Velocity = (UpdatedComponent->GetComponentLocation() - InitialLocation) / DeltaTime;
		}
	}

}

void USSTCharacterMovementComponent::PerformDash()
{
	PerformDashDelegate.Broadcast();
}

AOneWayPlatform* USSTCharacterMovementComponent::FindOneWayPlatform()
{
	FFindFloorResult FloorResult;
	FindFloor(UpdatedComponent->GetComponentLocation(), FloorResult, false);
	if (FloorResult.IsWalkableFloor())
	{
		AOneWayPlatform* OneWayPlatform = Cast<AOneWayPlatform>(FloorResult.HitResult.GetActor());
		if (OneWayPlatform)
		{
			return OneWayPlatform;
		}
	}
	return nullptr;
}

void USSTCharacterMovementComponent::AddInputVector(FVector WorldVector, bool bForce /* = false */)
{
	if (!MoveInputsEnabled) { return; }

	bool IsRightMotion = WorldVector.X > 0;
	if (IsRightMotion == FacingRight)
	{
		// This is movement in the direction we're facing, so add as normal
		Super::AddInputVector(WorldVector, bForce);
	}
	else if (!Turning && !HasRecentlyWalljumped)
	{
		// Motion in the reverse direction
		// Rather than realize this as rotation in our plane-constrained physics, 
		//  we ensure we do a full turn before adding any other input
		RequestTurnAround();
	}
}

bool USSTCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	bool InWallslide = CanWalljump();
	bool InDash = IsDashing;
	if (Super::DoJump(bReplayingMoves))
	{
		if (InWallslide)
		{
			PerformWallJump();
			ExitWallslide();
			SetMovementMode(MOVE_Falling);
		}
		else if (InDash)
		{
			ExitDash(true);
			SetMovementMode(MOVE_Falling);
		}
		return true;
	}
	return false;
}

bool USSTCharacterMovementComponent::CanCrouchInCurrentState() const
{
	return Super::CanCrouchInCurrentState() && !IsCustomMovementMode(FSSTMOVE_WALLSLIDING);
}

void USSTCharacterMovementComponent::SetFacingRight(bool bFacingRight)
{
	FacingRight = bFacingRight;
}

bool USSTCharacterMovementComponent::IsCustomMovementMode(ESSTCharacterMovementMode Mode) const
{
	return (MovementMode == MOVE_Custom) && (CustomMovementMode == (uint8)Mode);
}

bool USSTCharacterMovementComponent::CanWalljump() const
{
	return (IsWallsliding || HasRecentlyWallSlid) && !HasRecentlyWalljumped && WallslideJumpOffForce > 0.0f;
}

bool USSTCharacterMovementComponent::RequestTurnAround()
{
	if (Turning) { return false; }
	if (IsDashing && !CanTurnWhileDashing) { return false; }
	Turning = true;
	FacingRight = !FacingRight;
	return true;
}

void USSTCharacterMovementComponent::OnBeginWallslide_Implementation()
{
}

void USSTCharacterMovementComponent::OnEndWallslide_Implementation()
{
}

bool USSTCharacterMovementComponent::CanDash() const
{
	// Owner must be able to dash
	if (!DashEnabled || !SSTCharacterOwner->CanDash()) { return false; }

	// If midair dash count is limited, check if we've hit our max
	if (MaxDashesBeforeLanding >= 0 && CurrentDashesBeforeLanding >= MaxDashesBeforeLanding) { return false; }

	// Check whether we're still in dash cooldown
	if (GetWorld()->GetTimeSeconds() - LastDashTime < DashCooldownSeconds) { return false; }

	return true;
}

void USSTCharacterMovementComponent::OnBeginDash_Implementation()
{
}

void USSTCharacterMovementComponent::OnEndDash_Implementation()
{
}

void USSTCharacterMovementComponent::OnRep_IsWallsliding()
{
	if (IsWallsliding)
	{
		EnterWallslide();
	}
	else
	{
		ExitWallslide();
	}
	bNetworkUpdateReceived = true;
}

void USSTCharacterMovementComponent::OnRep_IsDashing()
{
	if (IsDashing)
	{
		WantsToDash = true;
		EnterDash();
	}
	else
	{
		WantsToDash = false;
		ExitDash();
	}
	bNetworkUpdateReceived = true;
}