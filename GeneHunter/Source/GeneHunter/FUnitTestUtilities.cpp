﻿#include "FUnitTestUtilities.h"


bool FUnitTestUtilities::Contains(const TArray<UType*>& Container, const UType* SearchTarget,
	const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](UType* Test) {
									if (bByName)
										return Test->GetName() == SearchTarget->GetName();
									return Test == SearchTarget;
								});
}

bool FUnitTestUtilities::Contains(const TArray<FTypeArray1*>& Container, const FTypeArray1* SearchTarget,
	const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](FTypeArray1* Test) {
									bool bFound = false;
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

}

bool FUnitTestUtilities::TypeArray1sAreEqual(const FTypeArray1& Actual, const FTypeArray1& Expected, FString& Description)
{
	return ArraysOfTypeAreEqual(Actual.TypeArray, Expected.TypeArray, Description);
}

bool FUnitTestUtilities::ArrayOfTypeArray1sAreEqual(const TArray<FTypeArray1*>& Actual,
	const TArray<FTypeArray1*>& Expected, FString& Description)
{
	bool bFound = true;
	for(FTypeArray1* TypeArray1 : Actual)
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

FString FUnitTestUtilities::TypeArray1ToFString(const FTypeArray1* TypeArray1)
{
	FString Ret = "[";
	for(UType* Type : TypeArray1->TypeArray)
		Ret += Type->GetName() + ", ";
	Ret += "]";
	Ret = Ret.Replace(TEXT(", ]"), TEXT("]"));
	return Ret;
}

FString FUnitTestUtilities::ArrayOfTypeArray1ToFString(const TArray<FTypeArray1*>& ArrayOfTypeArray1)
{
	FString Ret = "{";
	for(const FTypeArray1* TypeArray1 : ArrayOfTypeArray1)
		Ret += TypeArray1ToFString(TypeArray1) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("}"));
	return Ret;
}