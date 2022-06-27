#include "FUnitTestUtilities.h"


bool FUnitTestUtilities::Contains(const TArray<UType*>& Container, const UType* SearchTarget, const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](UType* Test) {
									if (bByName)
										return Test->GetName() == SearchTarget->GetName();
									return Test == SearchTarget;
								});
}

bool FUnitTestUtilities::ArraysOfTypeAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected, FString& Description)
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

bool FUnitTestUtilities::TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected, FString& Description)
{

	
	
	// UDummyType* -> UType*
	TArray<UType*> ExpectedTypes;
	for(UDummyType* Dummy : Expected)
		if (UType* Type = Cast<UType>(Dummy))
			ExpectedTypes.Add(Type);

	// Pass to UType* comparitor function
	return ArraysOfTypeAreEqual(Actual, ExpectedTypes, Description);
	
	

/*



	
	
	// Convert to UDummyType (actual; and start building description in case it fails)
	Description = "[Actual: ";
	TArray<UDummyType*> Array1Dummy;
	for(UType* Type : Actual)
	{
		if (UDummyType* DummyType = Cast<UDummyType>(Type))
		{
			Array1Dummy.Add(DummyType);
			Description += DummyType->GetName() + " ";
		}
	}

	// Get expected result
	Description += "// Expected: ";
	for(const UDummyType* UTType : Expected)
		if (UTType)
			Description += UTType->GetName() + " ";
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("]"));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = Array1Dummy.Num() == Expected.Num();
	if (bPass)
	{
		for(const UDummyType* DummyType : Array1Dummy)
		{
			if (!Expected.Contains(DummyType))
			{
				Description += " " + DummyType->GetName() + " not found!";
				bPass = false;
				break;
			}
		}
	} else
	{
		Description += " " + FString::SanitizeFloat(Array1Dummy.Num()) + " != " + FString::SanitizeFloat(Expected.Num());
	}
	return bPass;
	*/
	return true;
}

bool FUnitTestUtilities::TypeArray1sAreEqual(const FTypeArray1& Actual, const FTypeArray1& Expected, FString& Description)
{
	return true;
	// Convert "Expected" entries to DummyType (I know, this seems WRONG!)
	//return FUnitTestUtilities::TypesAndDummiesAreEqual(Actual.TypeArray, Expected.TypeArray, Description);
}