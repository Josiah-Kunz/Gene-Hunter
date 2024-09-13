
#include "ProjectileDependent.h"

void UProjectileDependent::InitializeComponent()
{
	Super::InitializeComponent();
	if (!Projectile)
	{
		Projectile = GetOwner()->FindComponentByClass<UProjectileMovementComponent>();
	}
}

void UProjectileDependent::InitializeProjectile(AActor* MoveCaster)
{
	Caster = MoveCaster;
}

void UProjectileDependent::Enable()
{
	SetComponentTickEnabled(true);
	InitializeProjectile(Caster);
}

void UProjectileDependent::Disable()
{
	SetComponentTickEnabled(false);
}
