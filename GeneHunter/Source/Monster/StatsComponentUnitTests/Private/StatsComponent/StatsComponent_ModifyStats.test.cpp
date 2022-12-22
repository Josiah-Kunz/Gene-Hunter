#pragma once

#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsComponent_ModifyStats,
	"__GeneHunter.FStat.StatsComponent.ModifyStats",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsComponent_ModifyStats::RunTest(const FString& Parameters)
{
	
	// Actual
	UStatsComponent* Actual = NewObject<UStatsComponent>();
	Actual->ModifyStatsUniformly(200, EStatValueType::Permanent, EModificationMode::SetDirectly);
	Actual->ModifyStatsUniformly(200, EStatValueType::Current, EModificationMode::SetDirectly);
	Actual->ModifyStatsUniformly(10, EStatValueType::Current, EModificationMode::AddPercentage);
	
	// Expected
	UStatsComponent* Expected = NewObject<UStatsComponent>();
	Expected->ModifyStatsUniformly(220, EStatValueType::Permanent, EModificationMode::SetDirectly);
	Expected->ModifyStatsUniformly(220, EStatValueType::Current, EModificationMode::SetDirectly);

	// Do test
	TestTrue("Modify Stats Uniformly",
		Actual->IsEqual(Expected, EStatValueType::Current));

	// Non-uniformly actual
	TArray<float> Mods = {-10, 0, -10, 0, -10};
	Actual->ModifyStats(Mods, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Non-uniformly expected
	Mods = {210, 220, 210, 220, 210, 220, 220};
	Expected->ModifyStats(Mods, EStatValueType::Current, EModificationMode::SetDirectly);

	// Non-uniform test
	TestTrue("Modify Stats Non-Uniformly",
		Actual->IsEqual(Expected, EStatValueType::Current));
	
	// Return
	return true;
}