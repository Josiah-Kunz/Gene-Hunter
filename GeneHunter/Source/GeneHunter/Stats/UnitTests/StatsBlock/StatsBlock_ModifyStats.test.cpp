#pragma once

#include "GeneHunter/Stats/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_ModifyStats,
	"FStat.StatsBlock.ModifyStats",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_ModifyStats::RunTest(const FString& Parameters)
{
	
	// Actual
	UStatsBlock* Actual = NewObject<UStatsBlock>();
	Actual->ModifyStatsUniformly(200, EStatValueType::CurrentAndPermanent, EModificationMode::SetDirectly);
	Actual->ModifyStatsUniformly(10, EStatValueType::Current, EModificationMode::AddPercentage);
	
	// Expected
	UStatsBlock* Expected = NewObject<UStatsBlock>();
	Expected->ModifyStatsUniformly(220, EStatValueType::CurrentAndPermanent, EModificationMode::SetDirectly);

	// Do test
	TestTrue("Modify Stats Uniformly",
		Actual->IsEqual(Expected, EStatValueType::Current));

	// Non-uniformly actual
	TArray<FStatModStruct> Mods = {
		{Actual->Health, -10},
		{Actual->PhysicalDefense, -10},
		{Actual->SpecialDefense, -10}
	}; 
	Actual->ModifyStats(Mods, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Non-uniformly expected
	Mods = {
		{Expected->Health, 210},
		{Expected->PhysicalAttack, 220},
		{Expected->PhysicalDefense, 210},
		{Expected->SpecialAttack, 220},
		{Expected->SpecialDefense, 210},
		{Expected->Haste, 220},
		{Expected->CriticalHit, 220}
	};
	Expected->ModifyStats(Mods, EStatValueType::Current, EModificationMode::SetDirectly);

	// Non-uniform test
	TestTrue("Modify Stats Non-Uniformly",
		Actual->IsEqual(Expected, EStatValueType::Current));
	
	// Return
	return true;
}