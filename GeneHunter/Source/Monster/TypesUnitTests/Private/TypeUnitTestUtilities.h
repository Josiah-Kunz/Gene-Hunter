#pragma once

#include "ConstLibrary.h"
#include "TypeArray2D.h"
#include "TypeUnitTestUtilities.generated.h"

UCLASS()
class UTypeUnitTestUtilities : public UBlueprintFunctionLibrary
{
	
public:

	GENERATED_BODY()
	
	constexpr static float TOLERANCE = 0.1F;

	constexpr static bool DEBUG = false;

	/**
		 * A macro to get "dummy" Types. These are special, independent of
		 *	in-game data (and hence are good for unit tests).
		 */
	#define GET_DUMMY_TYPES() \
		TArray<UType*> AllDummyTypes; \
		UType::GetAllTypes(AllDummyTypes, {}, true, true); \
		UType* Bug = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Bug-Dummy"))); \
		UType* Electric = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Electric-Dummy"))); \
		UType* Fighting = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Fighting-Dummy"))); \
		UType* Fire = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Fire-Dummy"))); \
		UType* Flying = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Flying-Dummy"))); \
		UType* Grass = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Grass-Dummy"))); \
		UType* Ground = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Ground-Dummy"))); \
		UType* Ice = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Ice-Dummy"))); \
		UType* Poison = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Poison-Dummy"))); \
		UType* Rock = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Rock-Dummy"))); \
		UType* Steel = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Steel-Dummy"))); \
		UType* Water = UType::GetTypeByName(AllDummyTypes, FName(TEXT("Water-Dummy")));
	
	/**
	 * Performs "UType::Analyze" depending on bAtk for unit tests. Returns if the result is equal to the expected
	 * values.
	 * For example:
	 *	- TypesToAnalyze = {Flying, Ground} (attackers)
	 *	- NumOpponentTypes = 2 (so we're getting all dual Type combinations)
	 *	- Range = FFloatRange{FFloatRangeBound::Exclusive(1), FFloatRangeBound::Open()} (only effective attacks)
	 *	- bAtk = true (confirms {Flying, Ground} are attackers)
	 *	- Mode = Coverage
	 *	- Expected = {new FTypeArray1D{{B.ug, Fighting}}, new FTypeArray1D{{B.ug, Fire}}, ...}
	 */
	static bool TestCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze, 
	const uint8 NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
	const TArray<FTypeArray1D>& Expected, FString& Description, const bool bDebug);

	/**
	 * Performs a test similar to TestCombatAnalysis, but for UType::AnalyzeAll.
	 */
	static bool TestAnalyzeAll(TArray<UType*>& AllTypes, const uint8 NumTestedTypes, const uint8 NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description);

};
