
#include "Type.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UType_CombineModifiers, "UType.CombineModifiers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UType_CombineModifiers::RunTest(const FString& Parameters)
{
	constexpr float Tolerance = 0.1F;

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2), -0.5F, Tolerance);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1), -1, Tolerance);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5), -1, Tolerance);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0), -1, Tolerance);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1), -1, Tolerance);

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1), -1, Tolerance);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0), 0, Tolerance);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5), 0, Tolerance);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1), 0, Tolerance);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2), 0, Tolerance);

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1, Tolerance);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0, Tolerance);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F, Tolerance);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F, Tolerance);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1, Tolerance);

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1, Tolerance);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0, Tolerance);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F, Tolerance);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1, Tolerance);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2, Tolerance);
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F, Tolerance);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0, Tolerance);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1, Tolerance);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2, Tolerance);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4, Tolerance);

	// All done!
	return true;
}
