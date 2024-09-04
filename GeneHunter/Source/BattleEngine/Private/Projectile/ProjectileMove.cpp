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
	Super::InitializeProjectile(MoveCaster);
	const AActor* Owner = GetOwner();

	// Make sure we have all dependents. If not, search for them.
	ENSURE_DEPENDENT(UProjectileMovementComponent, Projectile, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileDirection, Direction, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileSpeed, Speed, Owner)
	ENSURE_PROJECTILEDEPENDENT(UProjectileDamage, Damage, Owner)
	
}

void UProjectileMove::OnProjectileCollision(const AActor* OtherActor, const FHitResult HitResult)
{
}
