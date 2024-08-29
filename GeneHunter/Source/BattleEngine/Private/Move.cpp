#include "Move.h"

void UMove::Execute()
{
	MoveData->SpawnObjects(GetWorld());
	ResetCD();
}

void UMove::ResetCD()
{
	const float BaseCD = MoveData->BaseCooldown;
	const float Haste = Stats->GetStat(EStatEnum::Haste).GetCurrentValue();
	RemainingCD = BaseCD/(1+Haste/100.f);
}
