// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Type.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * SCompoundWidget that draws a UType "name plate".
 */
class TYPES_API STypePlate : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(STypePlate)
		:
	_Type(nullptr)
	, _Width(80)
	, _Height(20)
	, _CornerRadius(4)
		{}

	SLATE_ARGUMENT(UType*, Type)
	SLATE_ARGUMENT(float, Width)
	SLATE_ARGUMENT(float, Height)
	SLATE_ARGUMENT(float, CornerRadius)
	
	SLATE_END_ARGS()

public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SOverlay> MakeSlate(const FArguments& InArgs, FLinearColor Color, FText Name, FText Description) const;
};