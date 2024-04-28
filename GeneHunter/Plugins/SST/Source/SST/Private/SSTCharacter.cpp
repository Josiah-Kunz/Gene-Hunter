// Copyright 2024 NFB Makes Games. All Rights Reserved.

#include "SSTCharacter.h"
#include "SSTCharacterMovementComponent.h"
#include "FollowCameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "InputActionValue.h"


ASSTCharacter::ASSTCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<USSTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SSTCharacterMovementComponent = Cast<USSTCharacterMovementComponent>(GetCharacterMovement());

	// Create a configurable camera to follow the player
	FollowCamera = CreateDefaultSubobject<UFollowCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = false;

	// Disable controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ASSTCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		PlayerController->bShowMouseCursor = bShowMouseCursor;
	}

	// Inform movement component of our initial orientation
	SSTCharacterMovementComponent->SetFacingRight(GetActorForwardVector().X > 0);
}

void ASSTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASSTCharacter::JumpOrDrop);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASSTCharacter::ReleaseJump);

		//Crouching/Dropping
		EnhancedInputComponent->BindAction(CrouchDropAction, ETriggerEvent::Triggered, this, &ASSTCharacter::CrouchDrop);
		EnhancedInputComponent->BindAction(CrouchDropAction, ETriggerEvent::Completed, this, &ASSTCharacter::StopCrouchDrop);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASSTCharacter::Move);
		EnhancedInputComponent->BindAction(MouseMoveAction, ETriggerEvent::Triggered, this, &ASSTCharacter::MouseMove);

		//Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ASSTCharacter::Dash);
	}

}

void ASSTCharacter::Move(const FInputActionValue& Value)
{
	if (Controller && SSTCharacterMovementComponent)
	{
		float MovementValue = Value.Get<float>();
		SSTCharacterMovementComponent->AddInputVector(FVector::ForwardVector * MovementValue);
	}
}

void ASSTCharacter::MouseMove(const FInputActionValue& Value)
{
	if (Controller && SSTCharacterMovementComponent)
	{
		
		FViewport* Viewport = GetWorld()->GetGameViewport()->Viewport; 
		const int32 ViewWidth = Viewport->GetSizeXY().X;
		const int32 MouseX = Viewport->GetMouseX();


		float MovementValue = Value.Get<float>() * (MouseX > ViewWidth/2.f ? 1 : -1);
		SSTCharacterMovementComponent->AddInputVector(FVector::ForwardVector * MovementValue);
	}
}

void ASSTCharacter::JumpOrDrop_Implementation()
{
	if (bIsCrouched) // attempt to drop through platform, if any
	{
		SSTCharacterMovementComponent->WantsToPlatformDrop = true;
	}
	else
	{
		Jump();
	}
}

void ASSTCharacter::CrouchDrop_Implementation()
{
	if (CanCrouch())
	{
		Crouch();
	}
}

void ASSTCharacter::StopCrouchDrop_Implementation()
{
	UnCrouch();
}

bool ASSTCharacter::CanDash_Implementation() const
{
	// Default implementation: can dash out of any action
	// Note that dash cooldown and max dashes per jump are handled
	//   in the character movement component 
	return true;
}

void ASSTCharacter::Dash_Implementation()
{
	SSTCharacterMovementComponent->WantsToDash = true;
}

void ASSTCharacter::ReleaseJump_Implementation()
{
	StopJumping();
}

bool ASSTCharacter::CanCrouch() const
{
	if (SSTCharacterMovementComponent->IsFalling()) { return false; }
	if (SSTCharacterMovementComponent->IsWallsliding) { return false; }
	if (SSTCharacterMovementComponent->IsDashing) { return false; }

	return Super::CanCrouch();
}

void ASSTCharacter::StopJumping()
{
	IsJumpStale = false;
	Super::StopJumping();
}

void ASSTCharacter::ResetJumpState()
{
	// Implements a fix to the default Character class, as its behavior is to
	//   reset jump count if this method is called in any state other than "Falling"
	// When extending custom CharacterMovementComponent, we add other states
	//   that shouldn't reset jump (wallslide, walljump, dash...)
	// Reset count in Landed() instead. 
	bPressedJump = false;
	bWasJumping = false;
	JumpKeyHoldTime = 0.0f;
	JumpForceTimeRemaining = 0.0f;
}

void ASSTCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCurrentCount = 0;
	JumpCurrentCountPreJump = 0;
}

void ASSTCharacter::CheckJumpInput(float DeltaTime)
{
	// In the default Character class, holding jump beyond JumpMaxHoldTime 
	//   will automatically trigger another jump. We override this method to 
	//   achieve the more expected behavior: the player must release the button
	//   and press it again to trigger an additional jump. 

	JumpCurrentCountPreJump = JumpCurrentCount;

	if (SSTCharacterMovementComponent)
	{
		if (bPressedJump && (IsJumpProvidingForce() || !IsJumpStale))
		{
			IsJumpStale = true;

			if (GetWorld()->GetTimeSeconds() - SSTCharacterMovementComponent->GetLastDropThroughPlatformTime() > DropThroughPlatformJumpLockout)
			{
				// If this is the first jump and we're already falling,
				// then increment the JumpCount to compensate.
				const bool bFirstJump = JumpCurrentCount == 0;
				if (bFirstJump && SSTCharacterMovementComponent->IsFalling())
				{
					JumpCurrentCount++;
				}

				const bool bDidJump = CanJump() && SSTCharacterMovementComponent->DoJump(bClientUpdating);
				if (bDidJump)
				{
					// Transition from not (actively) jumping to jumping.
					if (!bWasJumping)
					{
						JumpCurrentCount++;
						JumpForceTimeRemaining = GetJumpMaxHoldTime();
						OnJumped();
					}
				}

				bWasJumping = bDidJump;
			}
		}
	}
}

FCollisionQueryParams ASSTCharacter::GetIgnoreSelfParams() const
{
	FCollisionQueryParams Params;
	TArray<AActor*> SelfChildren;

	GetAllChildActors(SelfChildren);
	Params.AddIgnoredActors(SelfChildren);
	Params.AddIgnoredActor(this);

	return Params;
}
