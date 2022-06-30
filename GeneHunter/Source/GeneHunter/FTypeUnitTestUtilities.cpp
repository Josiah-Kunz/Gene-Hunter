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

bool FTypeUnitTestUtilities::Contains(const TArray<FTypeArray1*>& Container, const FTypeArray1* SearchTarget,
	const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](const FTypeArray1* Test) {
									bool bFound = true;
									for(const UType* Type : SearchTarget->TypeArray)
									{
										if (Type)
										{
											bFound = true;
											if (!Contains(Test->TypeArray, Type, bByName))
											{
												bFound = false;
												break;
											}
										}
									}
									return bFound;
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
	Description += " // ";
	for(const UType* ActualType : Actual)
		if (ActualType)
			Description += ActualType->GetName() + " ";

	// Delete last space
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("]"));

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

bool FTypeUnitTestUtilities::TypeArray1sAreEqual(const FTypeArray1& Actual, const FTypeArray1& Expected, FString& Description)
{
	return ArraysOfTypeAreEqual(Actual.TypeArray, Expected.TypeArray, Description);
}

bool FTypeUnitTestUtilities::ArrayOfTypeArray1sAreEqual(const TArray<FTypeArray1*>& Actual,
	const TArray<FTypeArray1*>& Expected, FString& Description)
{
	bool bFound = true;
	for(const FTypeArray1* TypeArray1 : Actual)
	{
		bFound = Contains(Expected, TypeArray1);
		if (!bFound)
		{
			Description += "Did not find " + TypeArray1ToFString(TypeArray1) + " in " +
				ArrayOfTypeArray1ToFString(Expected) + "!";
			break;
		}
	}

	return bFound;
}

bool FTypeUnitTestUtilities::ArrayOfTypeArray2sAreEqual(const TArray<FTypeArray2*>& Actual,
	const TArray<FTypeArray2*>& Expected, FString& Description)
{

	/* Create 2 FTypeArray1 for each [Actual/Expected] by splitting:
	*	- Actual = {	FTypeArray2{{A, B, C}, {a, b, c}},
	*					FTypeArray2{{D, E, F}, {d, e, f}},
	*					...}
	*	- Actual1 = {	FTypeArray1{{A, B, C}},
	*					FTypeArray1{{D, E, F}},
	*					...}
	*	- Actual2 = {	FTypeArray1{{a, b, c}},
	*					FTypeArray1{{d, e, f}},
	*					...}
	*/
	TArray<FTypeArray1*> Actual1, Actual2;
	for(const FTypeArray2* TypeArray2 : Actual)
	{
		Actual1.Add(new FTypeArray1{TypeArray2->TypeArray});
		Actual2.Add(new FTypeArray1{TypeArray2->TypeArray2});
	}
	TArray<FTypeArray1*> Expected1, Expected2;
	for(const FTypeArray2* TypeArray2 : Expected)
	{
		Expected1.Add(new FTypeArray1{TypeArray2->TypeArray});
		Expected2.Add(new FTypeArray1{TypeArray2->TypeArray2});
	}
	return ArrayOfTypeArray1sAreEqual(Actual1, Expected1, Description) &&
		ArrayOfTypeArray1sAreEqual(Actual2, Expected2, Description);
}

FString FTypeUnitTestUtilities::TypeArray1ToFString(const FTypeArray1* TypeArray1)
{
	FString Ret = "[";
	for(const UType* Type : TypeArray1->TypeArray)
		Ret += Type->GetName() + ", ";
	Ret += "]";
	Ret = Ret.Replace(TEXT(", ]"), TEXT("]"));
	return Ret;
}

FString FTypeUnitTestUtilities::ArrayOfTypeArray1ToFString(const TArray<FTypeArray1*>& ArrayOfTypeArray1)
{
	FString Ret = "{";
	for(const FTypeArray1* TypeArray1 : ArrayOfTypeArray1)
		Ret += TypeArray1ToFString(TypeArray1) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("}"));
	return Ret;
}

bool FTypeUnitTestUtilities::DoCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze,
	const int NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
	const TArray<FTypeArray1*>& Expected, FString& Description)
{
	// Get array of FTypeArray1 (either defenders or attackers)
	const TArray<FTypeArray1*> OpponentTypes = UType::GetAllTypeCombinations(AllTypes, NumOpponentTypes);
	
	// Get the UTypes (actual) that fall within the given range
	const TArray<FTypeArray1*> Analysis = UType::Analyze(TypesToAnalyze, OpponentTypes,
				Range,
				Mode,
				bAtk,
				true
			);

	// Test it
	return ArrayOfTypeArray1sAreEqual(Analysis, Expected, Description);
}

bool FTypeUnitTestUtilities::DoAnalyzeAll(TArray<UType*>& AllTypes, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2*>& Expected, FString& Description)
{
	
	// Get the FTypeArray2 (actual) that fall within the given range
	TArray<FTypeArray2> Analysis = UType::AnalyzeAll(AllTypes, NumTestedTypes, NumUntestedTypes, Range, bAnalyzeAtk,
		Mode);
	TArray<FTypeArray2*> AnalysisPointer;
	for(FTypeArray2& TypeArray2 : Analysis)
		AnalysisPointer.Add(std::addressof(TypeArray2));

	// Test it
	return ArrayOfTypeArray2sAreEqual(AnalysisPointer, Expected, Description);
}
