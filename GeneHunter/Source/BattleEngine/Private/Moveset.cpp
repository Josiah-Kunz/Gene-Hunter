#include "Moveset.h"

UMoveset::UMoveset()
{
	PrimaryComponentTick.bCanEverTick = false;
}

uint8 UMoveset::MaxMoves() const
{
	// TODO: effect outlets
	return 4;
}

const TArray<UMove*> UMoveset::GetMoves() const
{
	return Moves;
}

void UMoveset::SetMoves(const TArray<UMove*> NewMoves)
{
	Moves = {};
	for(uint8 i=0; i<NewMoves.Num(); i++)
	{
		SetMoveByIndex(i, NewMoves[i]);
	}
}

bool UMoveset::SetMoveByIndex(const uint8 Index, UMove* NewMove)
{

	// Guard
	if (!IsValidIndex(Index))
	{
		return false;
	}

	// Set 'er done!
	while (Index > Moves.Num())
	{
		Moves.Add(nullptr);
	}
	Moves[Index] = NewMove;
	return true;
	
}

bool UMoveset::UseMoveByIndex(const uint8 Index)
{
	// Guard
	if (!IsValidIndex(Index))
	{
		return false;
	}

	// Dewet
	Moves[Index]->Execute();
	return true;
}

bool UMoveset::UseExistingMove(const UMove* Move)
{
	for(uint8 i=0; i<Moves.Num(); i++)
	{
		if (Move == Moves[i])
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

