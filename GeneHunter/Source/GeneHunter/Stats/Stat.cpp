// 


#include "Stat.h"

float UStat::StatJump(const int Level)
{
	return FMathf::Pow(3.0f, FMathf::Floor(Level/10.0f));
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

UStat::UStat()
{
	SetCurrentValue(1);
	SetPermanentValue(1);
}

void UStat::Update(const int Level)
{
	UpdatePermanent(Level, true);
}


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

void UStat::ModifyValue(const float Modifier, const EStatValueType ModifyType, const EModificationMode ModifyMode)
{
	switch(ModifyType)
	{
	case EStatValueType::Current:
		SetCurrentValue(GetModification(GetCurrentValue(), ModifyMode, Modifier));
		break;
	case EStatValueType::Permanent:
		SetPermanentValue(GetModification(GetPermanentValue(), ModifyMode, Modifier));
		break;
	case EStatValueType::CurrentAndPermanent:
		SetPermanentValue(GetModification(GetPermanentValue(), ModifyMode, Modifier));
		SetCurrentValue(GetModification(GetCurrentValue(), ModifyMode, Modifier));
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("ModifyMode not coded for in Stat::GetModification! Fix ASAP!"));
		break;
	}
}

FString UStat::ToString(const bool Inline)
{
	if (Inline)
	return FString::Printf(TEXT("%s | %s/%s | BaseStat: %s | BasePairs: %s |"),
		*Name(),
		*FString::FromInt(GetCurrentValue()),
		*FString::FromInt(GetPermanentValue()),
		*FString::FromInt(BaseStat),
		*FString::FromInt(BasePairs)
		);
	return FString::Printf(TEXT("%s\n\t%s/%s\n\tBaseStat: %s\n\tBasePairs: %s"),
		*Name(),
		*FString::FromInt(GetCurrentValue()),
		*FString::FromInt(GetPermanentValue()),
		*FString::FromInt(BaseStat),
		*FString::FromInt(BasePairs)
		);
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

float UStat::GetModification(const int Original, const EModificationMode Mode, const float Modification)
{
	switch(Mode)
	{

	// Addition
	case EModificationMode::AddAbsolute:
		return Original + Modification;
	case EModificationMode::AddFraction:
		return Original + Original * Modification;
	case EModificationMode::AddPercentage:
		return GetModification(Original, EModificationMode::AddFraction, Modification/100);

	// Multiplication
	case EModificationMode::MultiplyAbsolute:
		return Original * Modification;
	case EModificationMode::MultiplyPercentage:
		return Original * Modification/100;
		
	// Set directly
	case EModificationMode::SetDirectly:
		return Modification;

	// Unhandled
	default:
		UE_LOG(LogTemp, Error, TEXT("EModificationMode not coded for in Stat::GetModification! Fix ASAP!"));
		return Original;
	}
}


#pragma endregion