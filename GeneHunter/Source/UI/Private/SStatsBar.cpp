// Fill out your copyright notice in the Description page of Project Settings.


#include "SStatsBar.h"

#include "SlateOptMacros.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SStatsBar::Construct(const FArguments& InArgs)
{

#define ALIGN() \
	.HAlign(HAlign_Left) \
	.VAlign(VAlign_Center)

	// Geometries
	const float LabelX = InArgs._Margin.Left;
	const float TextBoxX = LabelX + InArgs._LabelSize.X + InArgs._Gap;
	const float SlashX = TextBoxX + InArgs._TextBoxSize.X + InArgs._Gap;
	const float MaxX = SlashX + InArgs._SlashSize.X + InArgs._Gap;
	const float MaxWidth = InArgs._MaxSize.X + (InArgs._IsPercentage.Get() ? PercentWidth : 0);
	const float BarX = MaxX + MaxWidth + InArgs._Gap - (InArgs._IsPercentage.Get() ? PercentWidth : 0);
	
	ChildSlot
	[
		SNew(SCanvas)

		// Text
		+SCanvas::Slot()[
			SNew(STextBlock)
				.Text(InArgs._LabelText)
				.ToolTipText(InArgs._LabelTooltip)
			]
			.Position(FVector2D{LabelX, 0})
			.Size(InArgs._LabelSize)
			ALIGN()

		// EditableText (Value)
		+SCanvas::Slot()[
		SNew(SEditableTextBox)
				.Text(FText::FromString(
					FString::Printf(TEXT("%s%s"),
					*InArgs._TextBoxText.ToString(),
					InArgs._IsPercentage.Get() ? *FString("%") : *FString("")
					)))
				.ToolTipText(InArgs._TextBoxTooltip)
				.OnTextCommitted_Lambda([InArgs](const FText& InText, ETextCommit::Type InTextCommit)
				{
					return InArgs._OnTextCommitted.Get().operator()(InText, InTextCommit);
				})
			]
			.Position(FVector2D{TextBoxX, 0})
			.Size(FVector2D{InArgs._TextBoxSize.X, InArgs._TextBoxSize.Y})
			ALIGN()

		// Slash
		+SCanvas::Slot()[
			SNew(STextBlock)
				.Text(InArgs._SlashText)
				.ToolTipText(InArgs._SlashTooltip)
			]
			.Position(FVector2D{SlashX, 0})
			.Size(InArgs._SlashSize)
			ALIGN()

		// Max
		+SCanvas::Slot()[
			SNew(STextBlock)
				.Text(FText::FromString(
						FString::Printf(TEXT("%s%s"),
						*InArgs._MaxText.ToString(),
						InArgs._IsPercentage.Get() ? *FString("% ") : *FString("")
						)
					))
				.ToolTipText(InArgs._MaxTooltip)
			]
			.Position(FVector2D{MaxX, 0})
			.Size(FVector2D{MaxWidth, InArgs._MaxSize.Y})
			ALIGN()
			
		// Bar outline
		+SCanvas::Slot()[
			SNew(SColorBlock)
				.Color(InArgs._OutlineColor)
				.ToolTipText(InArgs._BarTooltip)
				.CornerRadius(InArgs._CornerRadius)
			]
			.Position(FVector2D{BarX, 0})
			.Size(InArgs._BarSize)
			ALIGN()

		// Bar background
		+SCanvas::Slot()[
			SNew(SColorBlock)
				.Color(InArgs._BackgroundColor)
				.ToolTipText(InArgs._BarTooltip)
				.CornerRadius(InArgs._CornerRadius)
			]
			.Position(FVector2D{ InArgs._OutlineThickness + BarX, 0})
			.Size(FVector2D{InArgs._BarSize.X - 2*InArgs._OutlineThickness,
				InArgs._BarSize.Y - 2*InArgs._OutlineThickness})
			ALIGN()
			
		// Bar color
		+SCanvas::Slot()[
			SNew(SColorBlock)
				.UseSRGB(false)
				.Color(InArgs._BarColor)
				.ToolTipText(InArgs._BarTooltip)
				.CornerRadius(InArgs._CornerRadius)
			]
			.Position(FVector2D{BarX + InArgs._OutlineThickness, 0})
			.Size(FVector2D{(InArgs._BarSize.X - 2 * InArgs._OutlineThickness) * InArgs._BarFraction,
				InArgs._BarSize.Y - 2*InArgs._OutlineThickness})
			ALIGN()
			
		].VAlign(VAlign_Center)
	;
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
