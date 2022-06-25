#include "FUnitTestUtilities.h"

bool FUnitTestUtilities::TArrayAreEqual(const TArray<UType*> Array1, const TArray<UDummyType*> Array2, FString& Description)
{
	
	// Convert to UDummyType (actual; and start building description in case it fails)
	Description = "[Actual: ";
	TArray<UDummyType*> Array1_UTType;
	for(UType* Type : Array1)
	{
		if (UDummyType* UTType = Cast<UDummyType>(Type))
		{
			Array1_UTType.Add(UTType);
			Description += UTType->GetName() + " ";
		}
	}

	// Get expected result
	Description += "// Expected: ";
	for(const UDummyType* UTType : Array2)
		Description += UTType->GetName() + " ";
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("]"));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = Array1_UTType.Num() == Array2.Num();
	if (bPass)
	{
		for(const UDummyType* UTType : Array1_UTType)
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
