// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDamageMultiple.h"

#include "ComponentUtilities.h"
#include "ProjectileMove.h"


// Sets default values for this component's properties
UProjectileDamageMultiple::UProjectileDamageMultiple()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UProjectileDamageMultiple::InitializeProjectile(AActor* MoveCaster)
{

	// Supah
	Super::InitializeProjectile(MoveCaster);

	// Get MoveData from the local ProjectileMove
	//UProjectileMove* ProjectileMove = nullptr;
	const AActor* ProjectileActor = Projectile->GetOwner();
	SEARCH_FOR_COMPONENT(UProjectileMove, ProjectileMove, ProjectileActor)
	if (!ProjectileMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s requires a %s on the Projectile owner %s!"),
				*UProjectileDamageMultiple::StaticClass()->GetName(),
				*UProjectileMove::StaticClass()->GetName(),
				*ProjectileActor->GetName()
			)
		return;
	}
	MoveData = ProjectileMove->MoveData;

	// Get CombatStats from the Move's caster
	SEARCH_FOR_COMPONENT(UCombatStatsComponent, CasterStats, MoveCaster)
	if (!CasterStats)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s requires a %s on the casting owner %s!"),
				*UProjectileDamageMultiple::StaticClass()->GetName(),
				*UCombatStatsComponent::StaticClass()->GetName(),
				*MoveCaster->GetName()
			)
	}
}

void UProjectileDamageMultiple::OnProjectileCollision(const AActor* OtherActor, UCombatStatsComponent* EnemyStats)
{
	// Supah
	Super::OnProjectileCollision(OtherActor, EnemyStats);

	// Can we still damage or have we been spent?
	if (!bCanStillDamage)
	{
		return;
	}

	// Do damage
	EnemyStats->ApplyMoveData(MoveData, CasterStats);
	NumTimesDamaged++;
	if (NumTimesDamaged >= NumDamageTimes)
	{
		bCanStillDamage = false; // I know I can do the fancy schmancy "bCan = NumTimesDamaged < NumDamageTimes"
		if (KillAfterSpent)
		{
			ProjectileMove->EndProjectile();
		}
	}
	
}

