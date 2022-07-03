#include "TypeArray2D.h"

bool FTypeArray2D::Contains(const TArray<FTypeArray2D*>& Container, const FTypeArray2D* SearchTarget,
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
									return UType::ArraysAreEqual(SearchTarget->Array, Test->Array, Description) &&
										UType::ArraysAreEqual(SearchTarget->Array2, Test->Array2, Description);
								});
}

bool FTypeArray2D::ArrayOfTypeArray2DsAreEqual(const TArray<FTypeArray2D*>& Actual,
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

FString FTypeArray2D::TypeArray2DToFString(const FTypeArray2D* TypeArray2D)
{
	FString Ret = "{";
	Ret += UType::ArrayToFString(TypeArray2D->Array);
	Ret += ", ";
	Ret += UType::ArrayToFString(TypeArray2D->Array2);
	Ret += "} ";
	return Ret;
}

FString FTypeArray2D::ArrayOfTypeArray2DToFString(const TArray<FTypeArray2D*>& ArrayOfTypeArray2D)
{
	FString Ret = "{";
	for(const FTypeArray2D* TypeArray2D : ArrayOfTypeArray2D)
		Ret += TypeArray2DToFString(TypeArray2D) + " ";
	Ret += "}";
	Ret = Ret.Replace(TEXT(", }"), TEXT("} "));
	return Ret;
}

