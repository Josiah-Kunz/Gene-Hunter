#include "ProjectileDamage.h"

#include "CombatStatsComponent.h"

UProjectileDamage::UProjectileDamage()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProjectileDamage::InitializeProjectile(AActor* MoveCaster)
{
	Super::InitializeProjectile(MoveCaster);
	for(TSubclassOf<UActorSpawnScheme> SpawnClass : SpawnOnHit){
		UActorSpawnScheme* NewSpawnScheme = NewObject<UActorSpawnScheme>(MoveCaster, SpawnClass);
		SpawnOnHitInstances.Add(NewSpawnScheme);
	}
}

void UProjectileDamage::OnProjectileCollision(const AActor* OtherActor,	UCombatStatsComponent* EnemyStats)
{
	for(UActorSpawnScheme* SpawnScheme : SpawnOnHitInstances)
	{
		TArray<AActor*> SpawnedActors = {};
		SpawnScheme->Spawn(Caster, SpawnedActors);
	}
}

