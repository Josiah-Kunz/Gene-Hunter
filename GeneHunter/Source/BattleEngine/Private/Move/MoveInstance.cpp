#include "MoveInstance.h"

void FMoveInstance::Execute(AActor* Owner)
{
	MoveData->SpawnObjects(Owner);
	ResetCD();
}

void FMoveInstance::ResetCD()
{
	const float BaseCD = MoveData->BaseCooldown;
	const float Haste = Stats->GetStat(EStatEnum::Haste).GetCurrentValue();
	RemainingCD = BaseCD/(1+Haste/100.f);
}

bool FMoveInstance::IsValid() const
{
	return MoveData != nullptr;
}
