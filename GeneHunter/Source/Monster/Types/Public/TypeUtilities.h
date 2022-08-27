﻿#pragma once

#include "ConstLibrary.h"
#include "TypeArray2D.h"
#include "TypeUtilities.generated.h"

UCLASS()
class TYPES_API UTypeUtilities : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
	
public:

	/**
	 * If we're building a .tex file and a multicol goes over this, we'll truncate the column with "...".
	 */
	constexpr static int MaxLaTeXLines = 38;

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
	 * For example, for NumTypes = 2, this returns {{A, B}, {A, C}, {A, D}, ... }.
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
			const EAttackModifierMode Mode = EAttackModifierMode::Coverage,
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
	 * @param bTwoWay If true, the triad must be a two-way triad. For example, 2x attacking Fire > Grass > Water, but
	 *	also 0.5x attacking Fire < Grass < Water.
	 * @param Triads The returned array of possible triads, such as Pokemon's {{Fire, Grass, Water},
	 *	{Fighting, Dark, Psychic}}. 
	 */
	static void GetRockPaperScissors(const TArray<UType*>& Types, const bool bTwoWay, TArray<FTypeArray1D>& Triads);

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

	/**
	 * Gets ranges and labels for various effectivenesses. For example, when attacking (1, inf) => "Effective".
	 */
	static TMap<FFloatRange, FString> EffectivenessLabels(const bool bAtk);

	/**
	 * Gets ranges and labels for various effectivenesses when attacking. For example, (1, inf) => "Effective".
	 */
	static TMap<FFloatRange, FString> AtkEffectivenessLabels();

	/**
	 * Gets ranges and labels for various effectivenesses when defending. For example, (1, inf) => "Weak To".
	 */
	static TMap<FFloatRange, FString> DefEffectivenessLabels();
	
	static bool IncrementIndices(const TArray<UType*>& Types, TArray<int>& Indices);

	static bool FormsTriadSide(UType* Attacker, UType* Defender, const bool bTwoWay);
	
};
