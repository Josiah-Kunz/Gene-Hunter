#include "FUnitTestUtilities.h"

bool FUnitTestUtilities::TArrayAreEqual(const TArray<UType*> Array1, const TArray<UType_UnitTest*> Array2, FString& Description)
{
	
	// Convert to UType_UnitTest (actual; and start building description in case it fails)
	Description = "[Actual: ";
	TArray<UType_UnitTest*> Array1_UTType;
	for(UType* Type : Array1)
	{
		if (UType_UnitTest* UTType = Cast<UType_UnitTest>(Type))
		{
			Array1_UTType.Add(UTType);
			Description += UTType->GetName() + " ";
		}
	}

	// Get expected result
	Description += "// Expected: ";
	for(const UType_UnitTest* UTType : Array2)
		Description += UTType->GetName() + " ";
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("]"));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = Array1_UTType.Num() == Array2.Num();
	if (bPass)
	{
		for(const UType_UnitTest* UTType : Array1_UTType)
		{
			if (!Array2.Contains(UTType))
			{
				Description += " " + UTType->GetName() + " not found!";
				bPass = false;
				break;
			}
		}
	} else
	{
		Description += " " + FString::SanitizeFloat(Array1_UTType.Num()) + " != " + FString::SanitizeFloat(Array2.Num());
	}
	return bPass;
}
