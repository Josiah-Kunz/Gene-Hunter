// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Affinity.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/STextComboBox.h"


/**
 *
 */
class DETAILSPANELARCHITECT_API SAffinity : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SAffinity)
		:

	// Name
	// ====
	
	_OnComboBoxChanged([](TSharedPtr<FString> NewString, ESelectInfo::Type SelectType){})
	, _OnComboBoxOpening([](){})
	, _OnLockClicked([](){return FReply::Unhandled();})
	, _IsLockEnabled([](){return true;})

	// Value
	// =====

	// Geometry
	, _CirclePadding(2)
	, _CircleSizeEmpty(20)
	, _CircleSizeFilled(16)
	, _PlusMinusSize(12)

	// Tooltips
	, _MinusToolTipText(FText::FromString("Decrease max affinity points by 1."))
	, _PlusToolTipText(FText::FromString("Increase max affinity points by 1."))
	, _CircleToolTipText(FText::FromString("Click to set this as the current number of affinity points."))
	
	// Events
	, _OnMinusClicked([](){return FReply::Unhandled();})
	, _OnPlusClicked([](){return FReply::Unhandled();})
	, _OnCircleClicked([](const int AffinityIndex, const int CurrentPoints){return FReply::Unhandled();})
	, _Enabled([](){return true;})

		{}

	SLATE_ARGUMENT(FAffinity, Affinity)
	
	// Name
	// ====
	SLATE_ATTRIBUTE(TFunction<void(TSharedPtr<FString>, ESelectInfo::Type)>, OnComboBoxChanged)
	SLATE_ATTRIBUTE(TFunction<void()>, OnComboBoxOpening)
	SLATE_ATTRIBUTE(TFunction<FReply()>, OnLockClicked)
	SLATE_ATTRIBUTE(TFunction<bool()>, IsLockEnabled)

	// Value
	// =====
	
	// Geometry
	SLATE_ARGUMENT(float, CirclePadding)
	SLATE_ARGUMENT(float, CircleSizeEmpty)
	SLATE_ARGUMENT(float, CircleSizeFilled)
	SLATE_ARGUMENT(float, PlusMinusSize)

	// Tooltips
	SLATE_ARGUMENT(FText, MinusToolTipText)
	SLATE_ARGUMENT(FText, PlusToolTipText)
	SLATE_ARGUMENT(FText, CircleToolTipText)
	
	// Events
	SLATE_ATTRIBUTE(TFunction<FReply()>, OnMinusClicked)
	SLATE_ATTRIBUTE(TFunction<FReply()>, OnPlusClicked)
	SLATE_ATTRIBUTE(TFunction<FReply(const int, const int)>, OnCircleClicked)
	SLATE_ATTRIBUTE(TFunction<bool()>, Enabled)
	
	SLATE_END_ARGS()

public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};