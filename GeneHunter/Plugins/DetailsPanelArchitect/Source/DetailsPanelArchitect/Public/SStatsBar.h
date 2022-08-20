// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * SCompoundWidget that houses functions to look like a(n editable) stats bar:
 *		[Label] [EditableText] / [Max] [Baaaaaaar    ]
 */
class DETAILSPANELARCHITECT_API SStatsBar : public SCompoundWidget
{
public:

	inline static constexpr float PercentWidth = 8;
	
	SLATE_BEGIN_ARGS(SStatsBar)
		: _LabelSize(30, 20)
	, _TextBoxSize(58, 20)
	, _SlashText(FText::FromString("/"))
	, _SlashSize(10, 20)
	, _MaxSize(50, 20)
	, _BarSize(120, 20)
	, _BarColor(FLinearColor::Blue)
	, _BackgroundColor(0.01f, 0.01f, 0.01f)
	, _OutlineColor(FLinearColor::Black)
	, _OutlineThickness(2)
	, _CornerRadius(2, 2, 2, 2)
	, _Gap(2)
	, _Margin(2)
		{
		}

	// Label
	// =====
	SLATE_ARGUMENT(FText, LabelText)
	SLATE_ARGUMENT(FText, LabelTooltip)
	SLATE_ARGUMENT(FVector2D, LabelSize)

	// TextBox
	// =======
	SLATE_ARGUMENT(FText, TextBoxText)
	SLATE_ARGUMENT(FText, TextBoxTooltip)
	SLATE_ARGUMENT(FVector2D, TextBoxSize)
	SLATE_ATTRIBUTE(TFunction<void (const FText&, ETextCommit::Type&)>, OnTextCommitted)

	// Slash
	// =====
	SLATE_ARGUMENT(FText, SlashText)
	SLATE_ARGUMENT(FText, SlashTooltip)
	SLATE_ARGUMENT(FVector2D, SlashSize)

	// Max
	// ===
	SLATE_ARGUMENT(FText, MaxText)	
	SLATE_ARGUMENT(FText, MaxTooltip)
	SLATE_ARGUMENT(FVector2D, MaxSize)

	// Bar
	// ===
	SLATE_ARGUMENT(FVector2D, BarSize)
	SLATE_ARGUMENT(FText, BarTooltip)
	SLATE_ARGUMENT(FLinearColor, BarColor)
	SLATE_ARGUMENT(FLinearColor, BackgroundColor)
	SLATE_ARGUMENT(FLinearColor, OutlineColor)
	SLATE_ARGUMENT(float, BarFraction)
	SLATE_ARGUMENT(float, OutlineThickness)
	SLATE_ARGUMENT(FVector4, CornerRadius)
	SLATE_ATTRIBUTE(bool, UseFullWidth)

	// Settings
	// ========
	SLATE_ARGUMENT(float, Gap)
	SLATE_ARGUMENT(FMargin, Margin)
	SLATE_ATTRIBUTE(bool, IsPercentage)
	
	SLATE_END_ARGS()

public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
