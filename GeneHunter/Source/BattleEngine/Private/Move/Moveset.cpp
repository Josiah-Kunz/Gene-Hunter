#include "Moveset.h"

#include "MoveInstance.h"

UMoveset::UMoveset()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoveset::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for(FMoveInstance& MoveInstance : Moves)
	{
		if (MoveInstance.IsValid() && MoveInstance.RemainingCD > 0)
		{
			MoveInstance.RemainingCD -= DeltaTime;
		}
	}
}

uint8 UMoveset::MaxMoves() const
{
	// TODO: effect outlets
	return 4;
}

bool UMoveset::SetMoveByIndex(const uint8 Index, FMoveInstance& NewMove)
{

	// Guard
	if (!IsValidIndex(Index))
	{
		return false;
	}

	// Set 'er done!
	while (Index > Moves.Num())
	{
		Moves.Add({});
	} 
	Moves[Index] = NewMove;
	return true;
	
}

bool UMoveset::UseMoveByIndex(const uint8 Index)
{
	// Guard
	const bool bIsRealMove = IsValidIndex(Index) && Moves[Index].IsValid();
	if (!bIsRealMove)
	{
		const bool bIsValidIndex = IsValidIndex(Index);
		if (bIsValidIndex)
		{
			UE_LOG(LogTemp, Warning, TEXT("Move has no MoveData!"))
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Move isn't at a valid index [%i]"), Index)
		}
		return false;
	}

	// Dewet
	UseMoveInternal(Index);
	return true;
}

bool UMoveset::UseExistingMove(const FMoveInstance& Move)
{
	for(uint8 i=0; i<Moves.Num(); i++)
	{
		if (Move.MoveData == Moves[i].MoveData)
		{
			return UseMoveByIndex(i);
		}
	}
	return false;
}

bool UMoveset::IsValidIndex(const uint8 Index) const
{
	return Index < MaxMoves();
}

void UMoveset::SetCombatStats(UCombatStatsComponent* CombatStats)
{
	for(FMoveInstance& MoveInstance : Moves)
	{
		if (MoveInstance.IsValid())
		{
			MoveInstance.Stats = CombatStats;
		}
	}
}

#if WITH_EDITOR
void UMoveset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) 
		                           ? PropertyChangedEvent.Property->GetFName() 
		                           : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMoveset, Moves))
	{
		ValidateMoves();
	}
}
#endif

void UMoveset::ValidateMoves()
{
	const uint8 MaxArraySize = MaxMoves();
	if (Moves.Num() != MaxArraySize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moves array must have exactly [%i] elements. Setting it as such."), MaxArraySize);
		Moves.SetNum(MaxArraySize);
	}
}

bool UMoveset::UseMoveInternal(uint8 Index)
{
	// Check cooldown
	if (Moves[Index].RemainingCD <= 0)
	{
		Moves[Index].Execute(GetOwner());
		return true;
	}
	return false;
}

