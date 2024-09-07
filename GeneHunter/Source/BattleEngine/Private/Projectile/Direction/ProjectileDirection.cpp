#include "ProjectileDirection.h"

void UProjectileDirection::ApplyDirection()
{

	// Vars
	const float Speed = Projectile->Velocity.Length();
	const FVector Direction = GetDirection().GetSafeNormal();

	// Set velocity
	Projectile->Velocity = Speed * Direction;

	// Set rotation
	if (bRotateToDirection)
	{
		AActor* ProjectileActor = Projectile->GetOwner();
		const FRotator Rotation = Direction.Rotation();
		ProjectileActor->SetActorRotation(Rotation);
	}
}

void UProjectileDirection::InitializeProjectile(AActor* MoveCaster)
{
	Super::InitializeProjectile(MoveCaster);
	ApplyDirection();
}
