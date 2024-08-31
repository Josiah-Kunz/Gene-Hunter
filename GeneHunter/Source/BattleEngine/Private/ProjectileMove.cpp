// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileMove.h"


// Called when the game starts
void UProjectileMove::BeginPlay()
{
	Super::BeginPlay();

	// Make sure we have a projectile
	if (Projectile == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileMove [%s] is missing a UProjectileDirection! Make sure you add one in the editor before you play."),
				*this->GetPathName()
			);
	}

	// Make sure we have all dependents
	for(UProjectileDependent* Component : {Direction})
	{

		if (Component == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ProjectileMove [%s] is missing component(s)! Could be: [Direction]. Even if none is desired, you must attach a None type."),
				*this->GetPathName()
			);

		
		} else
		{
			
			// If the Component doesn't have a Projectile attached, be charitable and use ours
			if (Component->Projectile == nullptr)
			{
				Component->Projectile = Projectile;
			}

			// Initialize
			Component->InitializeProjectile();
		}
	}
	
}