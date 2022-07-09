// 


#include "Stat.h"

float UStat::StatJump(int Level)
{
	return FMathf::Pow(3, FMathf::Floor(Level/10.0f));
}

#pragma region Public functions for setters/getters

float UStat::GetCurrentValue()
{
	return CurrentValue;
}

void UStat::SetCurrentValue(const float NewValue)
{
	if (NewValue > 0)
		CurrentValue = NewValue;
}

float UStat::GetPermanentValue()
{
	return PermanentValue;
}

void UStat::SetPermanentValue(const float NewValue)
{
	if (NewValue > 0)
		PermanentValue = NewValue;
}

#pragma endregion

#pragma region Public functions

void UStat::UpdatePermanent(const int Level, const bool ResetCurrent)
{
	SetPermanentValue(CalculateValue(Level));
	if (ResetCurrent)
		SetCurrentValue(PermanentValue);
}

void UStat::UpdateCurrent(const int Level)
{
	SetCurrentValue(CalculateValue(Level));
}

void UStat::ModifyValue(const float Modifier, const EStatGainType GainType, const EModificationMode ModifyMode)
{
	switch(GainType)
	{
	case EStatGainType::Current:
		SetCurrentValue(ModifyValue(GetCurrentValue(), ModifyMode, Modifier));
		break;
	case EStatGainType::Permanent:
		SetPermanentValue(ModifyValue(GetPermanentValue(), ModifyMode, Modifier));
		break;
	case EStatGainType::CurrentAndPermanent:
		SetPermanentValue(ModifyValue(GetPermanentValue(), ModifyMode, Modifier));
		SetCurrentValue(ModifyValue(GetCurrentValue(), ModifyMode, Modifier));
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("ModifyMode not coded for in Stat::ModifyValue! Fix ASAP!"));
		break;
	}
}


#pragma endregion

#pragma region Things that should be overridden!

float UStat::CalculateValue(const int Level)
{
	return 1; // Override this!
}

FSupportingText const UStat::SupportingText() const
{
	FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("???"),
		FText::FromString("Oh no, the lazy devs forgot about this one!")
	};
	return SupportingText;
}

FString const UStat::Name() const
{
	const FString Name = FString{"???"};
	return Name;
}

FString const UStat::Abbreviation() const
{
	const FString Abbrev = FString{"???"};
	return Abbrev;
}

FLinearColor const UStat::Color() const
{
	const FLinearColor Color = FLinearColor{0, 0, 0};
	return Color;
}

#pragma endregion

#pragma region Private functions

int UStat::ModifyValue(const int Original, const EModificationMode Mode, const float Modification)
{

	float Ret = 1;
	switch(Mode)
	{

	// Addition
	case EModificationMode::AddAbsolute:
		Ret = Original + Modification;
		break;
	case EModificationMode::AddFraction:
		Ret = Original + Original * Modification;
		break;
	case EModificationMode::AddPercentage:
		Ret = ModifyValue(Original, EModificationMode::AddFraction, Modification/100);
		break;

	// Multiplication
	case EModificationMode::MultiplyAbsolute:
		Ret = Original * Modification;
		break;
	case EModificationMode::MultiplyPercentage:
		Ret = Original * Modification/100;
		break;

	// Unhandled
	default:
		UE_LOG(LogTemp, Error, TEXT("EModificationMode not coded for in Stat::ModifyValue! Fix ASAP!"));
		break;
	}

	// Round return value
	return FMathf::Round(Ret);
}


#pragma endregion