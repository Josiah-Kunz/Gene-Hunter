#include "FTypeUnitTestUtilities.h"


bool FTypeUnitTestUtilities::Contains(const TArray<UType*>& Container, const UType* SearchTarget,
                                      const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](UType* Test) {
									if (bByName)
										return Test->GetName() == SearchTarget->GetName();
									return Test == SearchTarget;
								});
}

bool FTypeUnitTestUtilities::Contains(const TArray<FTypeArray1D*>& Container, const FTypeArray1D* SearchTarget,
	const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](const FTypeArray1D* Test) {
									bool bFound = true;
									for(const UType* Type : SearchTarget->Array)
									{
										if (Type)
										{
											bFound = true;
											if (!Contains(Test->Array, Type, bByName))
											{
												bFound = false;
												break;
											}
										}
									}
									return bFound;
								});
}

bool FTypeUnitTestUtilities::Contains(const TArray<FTypeArray2D*>& Container, const FTypeArray2D* SearchTarget,
	FString& Description)
{

	/* The following should return true:
	*	- Container = {	FTypeArray2D{{A, B, C}, {a, b, c}},
	*					FTypeArray2D{{D, E, F}, {d, e, f}},
	*					...}
	*	- SearchTarget = FTypeArray2D{{C, B, A}, {a, c, b}}
	*/
	
	return std::any_of(std::begin(Container), std::end(Container),
								[&](const FTypeArray2D* Test) {
									return ArraysOfTypeAreEqual(SearchTarget->Array, Test->Array, Description) &&
										ArraysOfTypeAreEqual(SearchTarget->Array2, Test->Array2, Description);
								});
}

bool FTypeUnitTestUtilities::ArraysOfTypeAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected, FString& Description)
{

	// Start building string in case it fails
	Description += "[Expected: ";

	// Expected
	for(const UType* ExpectedType : Expected)
		if (ExpectedType)
			Description += ExpectedType->GetName() + " ";

	// Actual
	Description += " || Actual: ";
	for(const UType* ActualType : Actual)
		if (ActualType)
			Description += ActualType->GetName() + " ";

	// Delete last space
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("] "));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = Actual.Num() == Expected.Num();
	if (bPass)
	{
		for(const UType* ExpectedType : Expected)
		{
			if (!Contains(Actual, ExpectedType))
			{
				Description += " | Expected [" + ExpectedType->GetName() + "] not found!";
				bPass = false;
			}
		}
	} else
	{
		Description += " " + FString::SanitizeFloat(Actual.Num()) + " != " + FString::SanitizeFloat(Expected.Num());
	}
	return bPass;
	
}

bool FTypeUnitTestUtilities::TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected, FString& Description)
{
	
	// UDummyType* -> UType*
	TArray<UType*> ExpectedTypes;
	for(UDummyType* Dummy : Expected)
		if (UType* Type = Cast<UType>(Dummy))
			ExpectedTypes.Add(Type);

	// Pass to UType* comparitor function
	return ArraysOfTypeAreEqual(Actual, ExpectedTypes, Description);

}

bool FTypeUnitTestUtilities::TypeArray1DsAreEqual(const FTypeArray1D& Actual, const FTypeArray1D& Expected, FString& Description)
{
	return ArraysOfTypeAreEqual(Actual.Array, Expected.Array, Description);
}

bool FTypeUnitTestUtilities::ArrayOFTypeArray1DsAreEqual(const TArray<FTypeArray1D*>& Actual,
	const TArray<FTypeArray1D*>& Expected, FString& Description)
{
	bool bFound = true;
	for(const FTypeArray1D* TypeArray1D : Actual)
	{
		bFound = Contains(Expected, TypeArray1D);
		if (!bFound)
		{
			Description += "Did not find " + TypeArray1DToFString(TypeArray1D) + " in " +
				ArrayOFTypeArray1DToFString(Expected) + "!";
			break;
		}
	}

	return bFound;
}

bool FTypeUnitTestUtilities::ArrayOfTypeArray2DsAreEqual(const TArray<FTypeArray2D*>& Actual,
	const TArray<FTypeArray2D*>& Expected, FString& Description)
{

	/* The following two FTypeArray2D should be equal:
	*	- Actual = {	FTypeArray2D{{A, B, C}, {a, b, c}},
	*					FTypeArray2D{{D, E, F}, {d, e, f}},
	*					...}
	*	- Expected = {	FTypeArray2D{{D, F, E}, {e, f, d}},
	*					FTypeArray2D{{C, B, A}, {a, b, c}},
	*					...}
	*/
	bool bFound = true;
	for(const FTypeArray2D* TypeArray2D : Actual)
	{
		FString DummyString = "";
		bFound = Contains(Expected, TypeArray2D, DummyString);
		if (!bFound)
		{
			Description += "Did not find " + TypeArray2DToFString(TypeArray2D) + "in " + ArrayOfTypeArray2DToFString(Expected); 
			break;
		}
	}

	return bFound;
}

FString FTypeUnitTestUtilities::ArrayOfUTypeToFString(const TArray<UType*>& Array)
{
	FString Ret = "[";
	for(const UType* Type : Array)
		Ret += Type->GetName() + ", ";
	Ret += "]";
	Ret = Ret.Replace(TEXT(", ]"), TEXT("]"));
	return Ret;
}

FString FTypeUnitTestUtilities::TypeArray1DToFString(const FTypeArray1D* TypeArray1D)
{
	return ArrayOfUTypeToFString(TypeArray1D->Array);
}

FString FTypeUnitTestUtilities::TypeArray2DToFString(const FTypeArray2D* TypeArray2D)
{
	FString Ret = "{";
	Ret += ArrayOfUTypeToFString(TypeArray2D->Array);
	Ret += ", ";
	Ret += ArrayOfUTypeToFString(TypeArray2D->Array2);
	Ret += "} ";
	return Ret;
}

FString FTypeUnitTestUtilities::ArrayOFTypeArray1DToFString(const TArray<FTypeArray1D*>& ArrayOFTypeArray1D)
{
	FString Ret = "{";
	for(const FTypeArray1D* TypeArray1D : ArrayOFTypeArray1D)
		Ret += TypeArray1DToFString(TypeArray1D) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("} "));
	return Ret;
}

FString FTypeUnitTestUtilities::ArrayOfTypeArray2DToFString(const TArray<FTypeArray2D*>& ArrayOfTypeArray2D)
{
	FString Ret = "{";
	for(const FTypeArray2D* TypeArray2D : ArrayOfTypeArray2D)
		Ret += TypeArray2DToFString(TypeArray2D) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("} "));
	return Ret;
}

bool FTypeUnitTestUtilities::DoCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze,
	const int NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
	const TArray<FTypeArray1D*>& Expected, FString& Description)
{
	// Get array of FTypeArray1D (either defenders or attackers)
	const TArray<FTypeArray1D*> OpponentTypes = UType::GetAllTypeCombinations(AllTypes, NumOpponentTypes);
	
	// Get the UTypes (actual) that fall within the given range
	const TArray<FTypeArray1D*> Analysis = UType::Analyze(TypesToAnalyze, OpponentTypes,
				Range,
				Mode,
				bAtk,
				DEBUG
			);

	// Test it
	return ArrayOFTypeArray1DsAreEqual(Analysis, Expected, Description);
}

bool FTypeUnitTestUtilities::DoAnalyzeAll(TArray<UType*>& AllTypes, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description)
{
	
	// Get the FTypeArray2D (actual) that fall within the given range
	TArray<FTypeArray2D> Analysis;
	UType::AnalyzeAll(AllTypes, NumTestedTypes, NumUntestedTypes, Range, bAnalyzeAtk, Mode, Analysis);
	TArray<FTypeArray2D*> AnalysisPointer;
	for(FTypeArray2D& TypeArray2D : Analysis)
		AnalysisPointer.Add(std::addressof(TypeArray2D));

	// Test it
	return ArrayOfTypeArray2DsAreEqual(AnalysisPointer, Expected, Description);
}
