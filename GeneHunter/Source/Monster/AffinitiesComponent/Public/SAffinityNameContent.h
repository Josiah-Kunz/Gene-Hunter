// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Affinity.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/STextComboBox.h"

/**
 * SCompoundWidget that houses the "NameComponent" of an affinity slate. This is just the ComboBox and lock.
 */
class AFFINITIESCOMPONENT_API SAffinityNameContent : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SAffinityNameContent)
		:
	_OnComboBoxChanged([](TSharedPtr<FString> NewString, ESelectInfo::Type SelectType){})
	, _OnComboBoxOpening([](){})
	, _OnLockClicked([](){return FReply::Unhandled();})
	, _IsLockEnabled([](){return true;})
		{}

	SLATE_ARGUMENT(FAffinity, Affinity)
	SLATE_ATTRIBUTE(TFunction<void(TSharedPtr<FString>, ESelectInfo::Type)>, OnComboBoxChanged)
	SLATE_ATTRIBUTE(TFunction<void()>, OnComboBoxOpening)
	SLATE_ATTRIBUTE(TFunction<FReply()>, OnLockClicked)
	SLATE_ATTRIBUTE(TFunction<bool()>, IsLockEnabled)
	
	SLATE_END_ARGS()

public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> GetTypeNames() const;

public:
	TArray<TSharedPtr<FString>> TypeNames;
};