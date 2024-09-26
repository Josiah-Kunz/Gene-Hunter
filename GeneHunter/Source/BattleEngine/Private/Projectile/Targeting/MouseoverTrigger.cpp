#include "MouseoverTrigger.h"

#include "ComponentUtilities.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UMouseoverTrigger::UMouseoverTrigger()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UMouseoverTrigger::BeginPlay()
{

	// Supah
	Super::BeginPlay();

	// Get player's targeting component (if any)
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Player)
	{
		SEARCH_FOR_COMPONENT_OR_LOG(UPlayerTargetingComponent, PlayerTargetingComponent, Player);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on %s requires a %s from %s, but none were found!"),
			*UMouseoverTrigger::StaticClass()->GetName(),
			*GetOwner()->GetPathName(),
			*ACharacter::StaticClass()->GetName(),
			*(GET_MEMBER_NAME_CHECKED(UGameplayStatics, GetPlayerCharacter).ToString())
			)
	}

	// Begin cursor over
	BeginDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UMouseoverTrigger, SendMouseoverInfo));
	CollisionComponent->OnBeginCursorOver.Add(BeginDelegate);

	// End cursor over
	EndDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UMouseoverTrigger, RetractMouseoverInfo));
	CollisionComponent->OnBeginCursorOver.Add(EndDelegate);
	
}

void UMouseoverTrigger::SendMouseoverInfo(UPrimitiveComponent* TouchedComponent)
{
	if (PlayerTargetingComponent)
	{
		
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on %s requires a %s!"),
				*UMouseoverTrigger::StaticClass()->GetName(),
				*GetOwner()->GetPathName(),
				*UPlayerTargetingComponent::StaticClass()->GetName()
			)
	}
}

void UMouseoverTrigger::RetractMouseoverInfo(UPrimitiveComponent* TouchedComponent)
{
}

