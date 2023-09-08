#include "TypeUnitTestUtilities.h"

#include "DiffResults.h"
#include "TypeUtilities.h"


bool UTypeUnitTestUtilities::TestCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze,
                                                const uint8 NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
                                                const TArray<FTypeArray1D>& Expected, FString& Description, const bool bDebug)
{
	// Get array of FTypeArray1D (either defenders or attackers)
	TArray<FTypeArray1D> OpponentTypes;
	UTypeUtilities::GetAllTypeCombinations(AllTypes, NumOpponentTypes, OpponentTypes);

	// Get the UTypes (actual) that fall within the given range
	TArray<FTypeArray1D> Analysis;
	UTypeUtilities::Analyze(TypesToAnalyze, OpponentTypes,
				Range,
				Analysis,
				Mode,
				bAtk,
				bDebug
			);

	// Test it
	return FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Analysis, Expected, Description);
}

bool UTypeUnitTestUtilities::TestAnalyzeAll(TArray<UType*>& AllTypes, const uint8 NumTestedTypes, const uint8 NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description)
{
	
	// Get the FTypeArray2D (actual) that fall within the given range
	TArray<FTypeArray2D> Analysis;
	UTypeUtilities::AnalyzeAll(AllTypes, NumTestedTypes, NumUntestedTypes, Range, bAnalyzeAtk, Mode, Analysis);
	TArray<FTypeArray2D*> AnalysisPointer;
	for(FTypeArray2D& TypeArray2D : Analysis)
		AnalysisPointer.Add(std::addressof(TypeArray2D));

	// Test it
	return FTypeArray2D::ArrayOfTypeArray2DsAreEqual(AnalysisPointer, Expected, Description);
}


