#include "ProjectileDamage.h"

UProjectileDamage::UProjectileDamage()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProjectileDamage::InitializeProjectile(AActor* MoveCaster)
{
	Super::InitializeProjectile(MoveCaster);
}

void UProjectileDamage::OnProjectileCollision(const AActor* OtherActor, const FHitResult HitResult)
{
}

