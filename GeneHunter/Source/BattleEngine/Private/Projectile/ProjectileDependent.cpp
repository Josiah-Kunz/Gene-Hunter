
#include "ProjectileDependent.h"

void UProjectileDependent::InitializeComponent()
{
	Super::InitializeComponent();
	if (!Projectile)
	{
		Projectile = GetOwner()->FindComponentByClass<UProjectileMovementComponent>();
	}
}

void UProjectileDependent::InitializeProjectile()
{
}
