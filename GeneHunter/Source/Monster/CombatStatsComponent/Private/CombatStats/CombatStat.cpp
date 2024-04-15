#include"CombatStat.h"

#include "MathUtil.h"				// For inherited classes using, e.g., FMathf::Floor

float FCombatStat::StatJump(const uint16 Level)
{
	return FMathf::Pow(3.0f, FMathf::Floor(Level/10.0f));
}

#pragma region Public functions for setters/getters

float FCombatStat::GetCurrentValue() const
{
	return CurrentValue;
}

void FCombatStat::SetCurrentValue(const float NewValue)
{
	if (NewValue > 0)
		CurrentValue = NewValue;
	else
		CurrentValue = 0;
}

float FCombatStat::GetPermanentValue() const
{
	return PermanentValue;
}

void FCombatStat::SetPermanentValue(const float NewValue)
{
	if (NewValue > 0)
		PermanentValue = NewValue;
	else
		PermanentValue = 1;
}

#pragma endregion

#pragma region Public functions

void FCombatStat::Update(const uint16 Level, const bool bResetCurrent)
{
	UpdatePermanent(Level, true);
}


void FCombatStat::UpdatePermanent(const uint16 Level, const bool ResetCurrent)
{
	SetPermanentValue(CalculateValue(Level));
	if (ResetCurrent)
		SetCurrentValue(PermanentValue);
}

void FCombatStat::UpdateCurrent(const uint16 Level)
{
	SetCurrentValue(CalculateValue(Level));
}

void FCombatStat::ModifyValue(const float Modifier, const EStatValueType ModifyType, const EModificationMode ModifyMode,
	const EStatReferenceType ReferenceType, const float ReferenceValue)
{
	switch(ModifyType)
	{
	case EStatValueType::Current:
		
		SetCurrentValue(GetModification(GetCurrentValue(), ModifyMode, Modifier,
			ReferenceType, ReferenceValue));
		break;
	case EStatValueType::Permanent:
		SetPermanentValue(GetModification(GetPermanentValue(), ModifyMode, Modifier,
			ReferenceType, ReferenceValue));
		break;
	case EStatValueType::BaseStat:
		BaseStat = GetModification(BaseStat, ModifyMode, Modifier, ReferenceType, ReferenceValue);
		break;
	case EStatValueType::BasePairs:
		BasePairs = GetModification(BasePairs, ModifyMode, Modifier, ReferenceType, ReferenceValue);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("ModifyMode [%s] not coded for in Stat::GetModification! Fix ASAP!"),
				*UEnum::GetValueAsString(ModifyType)
			);
		break;
	}
}

float FCombatStat::GetValue(const EStatValueType ModifyType) const
{
	switch(ModifyType)
	{
	case EStatValueType::Current:
		return GetCurrentValue();
	case EStatValueType::Permanent:
		return GetPermanentValue();
	case EStatValueType::BaseStat:
		return BaseStat;
	case EStatValueType::BasePairs:
		return BasePairs;
	}
	UE_LOG(LogTemp, Warning, TEXT("Problem in FCombatStat::GetValue! Enum value not defined!"))
	return GetCurrentValue();
}

FString FCombatStat::ToString(const bool Inline) const
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

void FCombatStat::RandomizeBaseStat(const int32 Min, const int32 Max)
{
	BaseStat = FMath::RandRange(Min, Max);
}

void FCombatStat::RandomizeBasePairs(const int32 Min, const int32 Max)
{
	BasePairs = FMath::RandRange(Min, Max);
}


#pragma endregion

#pragma region Things that should be overridden!

float FCombatStat::CalculateValue(const uint16 Level)
{
	return 1; // Override this!
}

FSupportingText const FCombatStat::SupportingText() const
{
	FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("???"),
		FText::FromString("Oh no, the lazy devs forgot about this one!")
	};
	return SupportingText;
}

FString const FCombatStat::Name() const
{
	const FString Name = FString{"???"};
	return Name;
}

FString const FCombatStat::Abbreviation() const
{
	const FString Abbrev = FString{"???"};
	return Abbrev;
}

FLinearColor const FCombatStat::Color() const
{
	const FLinearColor Color = FLinearColor{0, 0, 0};
	return Color;
}

float FCombatStat::GetReferenceValue(const float SelfValue, const EStatReferenceType ReferenceType,
	const float OtherValue) const
{
	switch(ReferenceType)
	{
	case EStatReferenceType::Self:
		return SelfValue;
	case EStatReferenceType::Current:
		return CurrentValue;
	case EStatReferenceType::Permanent:
		return PermanentValue;
	case EStatReferenceType::SpecifiedValue:
		return OtherValue;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unsure how to handle StatReferenceType [%s]! Please code it in CombatStat.cpp."),
			*UEnum::GetValueAsString(ReferenceType)
		)
		return SelfValue;
	}
}

#pragma endregion

#pragma region Static functions

float FCombatStat::GetModification(const float Original, const EModificationMode Mode, const float Modification,
	const EStatReferenceType ReferenceType, const float ReferenceValue)
{
	
	switch(Mode)
	{

	// Addition
	case EModificationMode::AddAbsolute:
		return Original + Modification;
	case EModificationMode::AddFraction:
		return Original + GetReferenceValue(Original, ReferenceType, ReferenceValue) * Modification;
	case EModificationMode::AddPercentage:
		return GetModification(Original, EModificationMode::AddFraction, Modification/100, ReferenceType, ReferenceValue);

	// Multiplication
	case EModificationMode::MultiplyAbsolute:
		return Original * Modification;
	case EModificationMode::MultiplyPercentage:
		return GetReferenceValue(Original, ReferenceType, ReferenceValue)
			* Modification/100;
		
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