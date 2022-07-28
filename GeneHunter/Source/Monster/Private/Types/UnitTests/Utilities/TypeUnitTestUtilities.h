#pragma once

#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
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
	 * If we're building a .tex file and a multicol goes over this, we'll truncate the column with "...".
	 */
	constexpr static int MAX_LATEX_LINES = 38;

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
	const int NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
	const TArray<FTypeArray1D*>& Expected, FString& Description, const bool bDebug);

	/**
	 * Performs a test similar to TestCombatAnalysis, but for UType::AnalyzeAll.
	 */
	static bool TestAnalyzeAll(TArray<UType*>& AllTypes, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description);

	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void PrintStatistics(const int NumAttackers, const int NumDefenders, const FFloatRange Range,
		const EAttackModifierMode Mode, const bool bAtk, const bool bPrintToConsole, const bool bPrintToFile,
		UPARAM(DisplayName="Format LaTeX") const bool bPrintToFileLaTeX, UPARAM(ref) TArray<UType*>& Exclude,
		const FString PrintDirectory = "Content/Editor/Type-Advantage/Statistics-Output/");
	
	/**
	 * Lazily gets all Type combinations. If you care about performance, take a look at how AnalyzeAll handles the problem.
	 * For example, for NumTypes = 2, this returns {A, B}, {A, C}, {A, D}, ...
	 */
	static void GetAllTypeCombinations(const TArray<UType*>& Types, const int NumTypes,
		TArray<FTypeArray1D>& TypeCombinations);
	
	/**
	 * Example: 
		* - TypesToAnalyze is the attack combinations {Fire, Water}
		* - AgainstTypes are all possible defenders combinations of length 2 (returned from GetAllTypeCombinations(Types, 2)).
		*	For example, {{Fire, Grass}, {Fire, Water}, {Grass, Water}, ...}
		* - Range = (1, INFINITY)
		* - bAtk = true (since TypesToAnalyze is attacking)
		* - Using Pokemon rules, the returns should be:
		*	- If multitype:
		*		- Analysis[0].Array = {Steel, Normal}		(because Fire = 2x and Water = 1x)
		*		- Analysis[1].Array = {Ground, Electric}	(because Fire = 1x and Water = 2x)
		*		- ...
		*	- If coverage:
		*		- Analysis[0].Array = {Grass, Normal}		(because Fire alone would suffice)
		*		- Analysis[1].Array = {Fire, Rock}			(because Water alone would suffice)
		*		- ...
	 */
	UFUNCTION(BlueprintCallable)
	static void Analyze(
			const TArray<UType*>& TypesToAnalyze,
			const TArray<FTypeArray1D>& AgainstTypes,
			const FFloatRange Range,
			TArray<FTypeArray1D>& Analysis,
			const EAttackModifierMode Mode = EAttackModifierMode::MultiType,
			const bool bAtk = true,
			const bool bDebug = false
			);

	/**
	 * Performs an analysis on the given Types.
	 *		- If bAnalyzeAtk, the "tested" Types are the attackers and the "untested" Types are the defenders.
	 *		- Ex: AnalyzeAll([all], 1, 1, [1, open), true) ==> all attacks that are 1v1 never resisted (e.g., Typeless would be in that result).
	 *
	 * The returned FTypeArray2D is broken into:
	 *	- Indices, e.g., Ret[0] for the data on the first attack combination
	 *	- Attacking combination, e.g., Ret[0].Array could yield {Fire, Water} as the attackers
	 *	- Defending combinations that fall within the given range, e.g., Ret[0].TypeArray2D could yield
	 *		{Grass, Normal,
	 *			Fire, Rock,
	 *			...}
	 *			(It's up to you to parse this array. In this example, do %2.)
	 */
	static void AnalyzeAll(TArray<UType*>& Types, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode, TArray<FTypeArray2D>& Result);

	/**
	 * Gets the "rock-paper-scissors" Type triads, such as Pokemon's Fire > Grass > Water.
	 * @param Types The Types to analyze.
	 * @param bTwoWay If true, the triad must be a two-way triad. For example, 2x attacking Fire > Grass > Water, but also 0.5x attacking Fire < Grass < Water.
	 * @param Triads The returned array of possible triads, such as Pokemon's {{Fire, Grass, Water}, {Fighting, Dark, Psychic}}. 
	 */
	static void GetRockPaperScissors(const TArray<UType*>& Types, const bool bTwoWay, TArray<FTypeArray1D*>& Triads);

	/**
	 * Prints all "rock-paper-scissors" Type triad, such as Pokemon's Fire > Grass > Water.
	 * @param bTwoWay If true, the triad must be a two-way triad. For example, 2x attacking Fire > Grass > Water, but also 0.5x attacking Fire < Grass < Water. 
	 */
	UFUNCTION(BlueprintCallable)
	static void PrintRockPaperScissors(const bool bTwoWay);

	/**
	 * Converts, e.g.,:
	 *	- TypeArray1D{ {A, B}, {C, D} } ==> {A, B, C, D}
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void ArrayOfTypeArray1DToArrayOfTypes(UPARAM(ref) const TArray<FTypeArray1D>& Original,
		TArray<UType*>& Result);

	/**
	 * Converts, e.g.,:
	 *  - Wrap = 2
	 *	- {A, B, C, D} ==> TypeArray1D{ {A, B}, {C, D} }
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void ArrayOfTypesToArrayOfTypeArray1D(UPARAM(ref) const TArray<UType*>& Original,
		TArray<FTypeArray1D>& Result, const int Wrap = 1);

private:

	static bool IncrementIndices(const TArray<UType*>& Types, TArray<int>& Indices);

	static bool FormsTriadSide(UType* Attacker, UType* Defender, const bool bTwoWay);
	
};
