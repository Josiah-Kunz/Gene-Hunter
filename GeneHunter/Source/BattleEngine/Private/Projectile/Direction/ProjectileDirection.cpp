#include "ProjectileDirection.h"

void UProjectileDirection::ApplyDirection()
{
	const float Speed = Projectile->Velocity.Length();
	Projectile->Velocity = Speed * GetDirection().GetSafeNormal();
}

void UProjectileDirection::InitializeProjectile()
{
	Super::InitializeProjectile();
	ApplyDirection();
}
