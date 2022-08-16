// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class UI_API SMySlateWidget : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SMySlateWidget)
		{}
	
	SLATE_ARGUMENT(FSlateBrush*, Brush)

	/** Called when the background is clicked */
	SLATE_EVENT( FOnClicked, OnClicked )

	SLATE_END_ARGS()

protected:
	FInvalidatableBrushAttribute Brush;

private:

	TSharedPtr<SImage> BackgroundImage;

	TSharedPtr<SButton> Button;
	
public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

protected:

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
};
