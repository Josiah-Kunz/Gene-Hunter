#pragma once
#include "Type_UnitTest.h"

class UnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	static bool TArrayAreEqual(const TArray<UType*> Array1, const TArray<UType_UnitTest*> Array2, FString& Description);
	
};
