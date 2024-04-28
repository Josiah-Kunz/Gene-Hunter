// Copyright 2024 NFB Makes Games. All Rights Reserved.


#include "OneWayPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SSTCharacter.h"

AOneWayPlatform::AOneWayPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set up components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);	
	
	BelowTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BelowTrigger"));
	BelowTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOneWayPlatform::BeginPlay()
{
	Super::BeginPlay();

	BelowTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOneWayPlatform::OnOverlapBeginBelowTrigger);
	BelowTrigger->OnComponentEndOverlap.AddDynamic(this, &AOneWayPlatform::OnOverlapEndBelowTrigger);
}

void AOneWayPlatform::OnOverlapBeginBelowTrigger_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CanPassThroughFromBelow) { return; }

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		SetCharacterIgnoreComponentWhenMoving(Character, true);
	}
}

void AOneWayPlatform::OnOverlapEndBelowTrigger_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!CanPassThroughFromBelow) { return; }

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		SetCharacterIgnoreComponentWhenMoving(Character, false);
	}
}

void AOneWayPlatform::RequestCharacterPassthrough(ACharacter* Character)
{
	SetCharacterIgnoreComponentWhenMoving(Character, true);
}

void AOneWayPlatform::SetCharacterIgnoreComponentWhenMoving(ACharacter* Character, bool bShouldIgnore)
{
	UPrimitiveComponent* RootPrimitiveComponent = Cast<UPrimitiveComponent>(Character->GetRootComponent());
	if (RootPrimitiveComponent)
	{
		RootPrimitiveComponent->IgnoreComponentWhenMoving(StaticMesh, bShouldIgnore);
	}
}
