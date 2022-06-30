#pragma once
#include "Types/Type.h"
#include <algorithm>
#include "Types/UnitTests/DummyType.h"

class FTypeUnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	constexpr static bool DEBUG = false;

	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<UType*>& Container, const UType* SearchTarget,
		const bool bByName = true);
	
	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<FTypeArray1D*>& Container, const FTypeArray1D* SearchTarget,
		const bool bByName = true);

	/**
	 * Determines if SearchTarget is inside Container (by name).
	 */
	static bool Contains(const TArray<FTypeArray2D*>& Container, const FTypeArray2D* SearchTarget,
		FString& Description);

	/**
	 * Tests if the arrays of Type* and DummyType* are equal (by name).
	 */
	static bool TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected,
		FString& Description);

	/**
	 * Tests if the arrays of Type* and Type* are equal (by name).
	 */
	static bool ArraysOfTypeAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected,
		FString& Description);

	/**
	 * Tests if two TypeArray1D are equal by simply checking if their FTypeArray1D.Array are equal.
	 */
	static bool TypeArray1DsAreEqual(const FTypeArray1D& Actual, const FTypeArray1D& Expected, FString& Description);

	/**
	 * Determines if
	 *	- Actual[i].Array[j] == Expected[k].Array[l]
	 *	
	 * for any i, j, k, l (by name comparison).
	 * 
	 *	- For example, [{A, B}, {a, b}] should equal [{b, a}, {A, B}]
	 */ 
	static bool ArrayOFTypeArray1DsAreEqual(const TArray<FTypeArray1D*>& Actual, const TArray<FTypeArray1D*>& Expected,
		FString& Description);

	/**
	 * Uses ArrayOFTypeArray1DsAreEqual.
	 */
	static bool ArrayOfTypeArray2DsAreEqual(const TArray<FTypeArray2D*>& Actual, const TArray<FTypeArray2D*>& Expected,
		FString& Description);


	/**
	 * Returns, e.g., "[Air, Earth, Fire, Water]".
	 */
	static FString ArrayOfUTypeToFString(const TArray<UType*>& Array);
	
	/**
	 * Returns, e.g., "[Air, Earth, Fire, Water]".
	 */
	static FString TypeArray1DToFString(const FTypeArray1D* TypeArray1D);

	/**
	 * Returns, e.g., "{[Air, Earth], [Fire, Water]}".
	 */
	static FString TypeArray2DToFString(const FTypeArray2D* TypeArray2D);

	/**
	 * Returns, e.g., "{[Air, Earth], [Fire, Water]}".
	 */
	static FString ArrayOFTypeArray1DToFString(const TArray<FTypeArray1D*>& ArrayOFTypeArray1D);

	/**
	 * Returns, e.g., "<{[Air, Earth], [Fire, Water]}, {[Flying, Ground], [Ice, Steel]}>". 
	 */
	static FString ArrayOfTypeArray2DToFString(const TArray<FTypeArray2D*>& ArrayOfTypeArray2D);

	/**
	 * Performs "UType::Analyze" depending on bAtk. Returns if the result is equal to the expected values.
	 * For example:
	 *	- TypesToAnalyze = {Flying, Ground} (attackers)
	 *	- NumOpponentTypes = 2 (so we're getting all dual Type combinations)
	*	- Range = FFloatRange{FFloatRangeBound::Exclusive(1), FFloatRangeBound::Open()} (only effective attacks)
	 *	- bAtk = true (confirms {Flying, Ground} are attackers)
	 *	- Mode = Coverage
	 *	- Expected = {new FTypeArray1D{{B.ug, Fighting}}, new FTypeArray1D{{B.ug, Fire}}, ...}
	 */
	static bool DoCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze, 
		const int NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray1D*>& Expected, FString& Description);

	/**
	 * Performs a test similar to DoCombatAnalysis, but for UType::AnalyzeAll.
	 */
	static bool DoAnalyzeAll(TArray<UType*>& AllTypes, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description);
	
	/**
	 * A macro to get "dummy" Types. These are of type UDummyType and inherit from UType. These are independent of
	 *	in-game data (and hence are good for unit tests).
	 */
#define GET_DUMMY_TYPES() \
	TArray<UDummyType*> AllDummyTypes; \
	UDummyType::GetAllDummyTypes(AllDummyTypes); \
	UDummyType* Bug = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Bug-Dummy"))); \
	UDummyType* Electric = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Electric-Dummy"))); \
	UDummyType* Fighting = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fighting-Dummy"))); \
	UDummyType* Fire = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fire-Dummy"))); \
	UDummyType* Flying = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Flying-Dummy"))); \
	UDummyType* Grass = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Grass-Dummy"))); \
	UDummyType* Ground = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ground-Dummy"))); \
	UDummyType* Ice = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ice-Dummy"))); \
	UDummyType* Poison = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Poison-Dummy"))); \
	UDummyType* Rock = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Rock-Dummy"))); \
	UDummyType* Steel = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Steel-Dummy"))); \
	UDummyType* Water = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Water-Dummy"))); 
	
};
