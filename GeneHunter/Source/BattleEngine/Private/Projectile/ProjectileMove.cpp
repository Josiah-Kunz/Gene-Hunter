// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileMove.h"

#include "ComponentUtilities.h"

#pragma region Macros

#define ENSURE_DEPENDENT(BaseType, Variable, Owner) \
	if ( Variable == nullptr){\
		SEARCH_FOR_COMPONENT( BaseType , Variable , Owner ) \
		if ( Variable == nullptr){\
			UE_LOG(LogTemp, Warning, TEXT("ProjectileMove [%s] is missing [%s]! Make sure you add one in the editor before you play."), \
				*this->GetPathName(), \
				* BaseType##::StaticClass()->GetName() \
			); \
		} \
	}

#define ENSURE_PROJECTILEDEPENDENT(BaseType, Variable, Owner) \
	ENSURE_DEPENDENT( BaseType , Variable , Owner )\
	if ( Variable ){\
		/* If the Component doesn't have a Projectile attached, be charitable and use ours */ \
		if ( Variable ->Projectile == nullptr) \
		{ \
			Variable ->Projectile = Projectile; \
		} \
		/* Initialize */ \
		Variable ->InitializeProjectile( Caster ); \
	}

#pragma endregion

// Called when the game starts
void UProjectileMove::InitializeProjectile(AActor* MoveCaster)
{

	// Basics
	Super::InitializeProjectile(MoveCaster);
	const AActor* Owner = GetOwner();

	// Check that MoveData is null (user error, but hey, it happens)
	if (MoveData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Oh, no. This is embarassing. You've forgotten to assign a MoveData to the Projectile %s!"),
				*this->GetOwner()->GetName()
			)
		return;
	}

	// Make sure we have all dependents. If not, search for them.
	ENSURE_DEPENDENT(UProjectileMovementComponent, Projectile, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileDirection, Direction, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileSpeed, Speed, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileDamage, Damage, Owner)

	// Done!
	bInitialized = true;
}

void UProjectileMove::OnProjectileCollision(const AActor* OtherActor, UCombatStatsComponent* EnemyStats)
{

	// Are we ready?
	if (!bInitialized)
	{
		return;
	}
	
	// Make sure this isn't the caster
	if (OtherActor != Damage->Caster)
	{
		Damage->OnProjectileCollision(OtherActor, EnemyStats);
	}
}
