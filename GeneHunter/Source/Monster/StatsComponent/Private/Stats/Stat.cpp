#include "Stat.h"

#include "MathUtil.h"				// For inherited classes using, e.g., FMathf::Floor

float FStat::StatJump(const int Level)
{
	return FMathf::Pow(3.0f, FMathf::Floor(Level/10.0f));
}

#pragma region Public functions for setters/getters

float FStat::GetCurrentValue() const
{
	return CurrentValue;
}

void FStat::SetCurrentValue(const float NewValue)
{
	if (NewValue > 0)
		CurrentValue = NewValue;
	else
		CurrentValue = 0;
}

float FStat::GetPermanentValue() const
{
	return PermanentValue;
}

void FStat::SetPermanentValue(const float NewValue)
{
	if (NewValue > 0)
		PermanentValue = NewValue;
	else
		PermanentValue = 1;
}

#pragma endregion

#pragma region Public functions

void FStat::Update(const int Level, const bool bResetCurrent)
{
	UpdatePermanent(Level, true);
}


void FStat::UpdatePermanent(const int Level, const bool ResetCurrent)
{
	SetPermanentValue(CalculateValue(Level));
	if (ResetCurrent)
		SetCurrentValue(PermanentValue);
}

void FStat::UpdateCurrent(const int Level)
{
	SetCurrentValue(CalculateValue(Level));
}

void FStat::ModifyValue(const float Modifier, const EStatValueType ModifyType, const EModificationMode ModifyMode)
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
	case EStatValueType::BaseStat:
		BaseStat = GetModification(BaseStat, ModifyMode, Modifier);
		break;
	case EStatValueType::BasePairs:
		BasePairs = GetModification(BasePairs, ModifyMode, Modifier);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("ModifyMode not coded for in Stat::GetModification! Fix ASAP!"));
		break;
	}
}

float FStat::GetValue(const EStatValueType ModifyType)
{
	switch(ModifyType)
	{
	case EStatValueType::Current:
		return GetCurrentValue();
	case EStatValueType::Permanent:
		return GetPermanentValue();
	case EStatValueType::CurrentAndPermanent:
		UE_LOG(LogTemp, Warning, TEXT("Problem in FStat::GetValue! \"CurrentAndPermanent\" not well defined!"))
		return GetCurrentValue();
	case EStatValueType::BaseStat:
		return BaseStat;
	case EStatValueType::BasePairs:
		return BasePairs;
	}
	UE_LOG(LogTemp, Warning, TEXT("Problem in FStat::GetValue! Enum value not defined!"))
	return GetCurrentValue();
}

FString FStat::ToString(const bool Inline) const
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

void FStat::RandomizeBaseStat(const int Min, const int Max)
{
	BaseStat = FMath::RandRange(Min, Max);
}

void FStat::RandomizeBasePairs(const int Min, const int Max)
{
	BasePairs = FMath::RandRange(Min, Max);
}


#pragma endregion

#pragma region Things that should be overridden!

float FStat::CalculateValue(const int Level)
{
	return 1; // Override this!
}

FSupportingText const FStat::SupportingText() const
{
	FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("???"),
		FText::FromString("Oh no, the lazy devs forgot about this one!")
	};
	return SupportingText;
}

FString const FStat::Name() const
{
	const FString Name = FString{"???"};
	return Name;
}

FString const FStat::Abbreviation() const
{
	const FString Abbrev = FString{"???"};
	return Abbrev;
}

FLinearColor const FStat::Color() const
{
	const FLinearColor Color = FLinearColor{0, 0, 0};
	return Color;
}

#pragma endregion

#pragma region Private functions

float FStat::GetModification(const int Original, const EModificationMode Mode, const float Modification)
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