#include "TypeArray1D.h"
#include <algorithm>


bool FTypeArray1D::Contains(const TArray<FTypeArray1D*>& Container, const FTypeArray1D* SearchTarget,
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
											if (!UType::Contains(Test->Array, Type, bByName))
											{
												bFound = false;
												break;
											}
										}
									}
									return bFound;
								});
}

bool FTypeArray1D::TypeArray1DsAreEqual(const FTypeArray1D& Actual, const FTypeArray1D& Expected, FString& Description)
{
	return UType::ArraysAreEqual(Actual.Array, Expected.Array, Description);
}

bool FTypeArray1D::ArrayOfTypeArray1DsAreEqual(const TArray<FTypeArray1D*>& Actual,
	const TArray<FTypeArray1D*>& Expected, FString& Description)
{
	bool bFound = true;
	for(const FTypeArray1D* TypeArray1D : Actual)
	{
		bFound = Contains(Expected, TypeArray1D);
		if (!bFound)
		{
			Description += "Did not find " + TypeArray1DToFString(TypeArray1D) + " in " +
				ArrayOfTypeArray1DToFString(Expected) + "!";
			break;
		}
	}

	return bFound;
}

FString FTypeArray1D::TypeArray1DToFString(const FTypeArray1D* TypeArray1D)
{
	return UType::ArrayToFString(TypeArray1D->Array);
}

FString FTypeArray1D::ArrayOfTypeArray1DToFString(const TArray<FTypeArray1D*>& ArrayOfTypeArray1D)
{
	FString Ret = "{";
	for(const FTypeArray1D* TypeArray1D : ArrayOfTypeArray1D)
		Ret += TypeArray1DToFString(TypeArray1D) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("} "));
	return Ret;
}