// Fill out your copyright notice in the Description page of Project Settings.


#include "SMySlateWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMySlateWidget::Construct(const FArguments& InArgs)
{

	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	ChildSlot
	[
		SAssignNew(Image, SImage)
	];

}

int32 SMySlateWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{

	// Color
	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	FLinearColor LinearColor = ColorAndOpacity.Get() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);




	// Draw!
	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*SlateBrush);
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		SlateBrush
		);
	
	return LayerId;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
