#include "Speed/ProjectileSpeed.h"

UProjectileSpeed::UProjectileSpeed()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProjectileSpeed::InitializeProjectile(AActor* MoveCaster)
{
	Super::InitializeProjectile(MoveCaster);
}

