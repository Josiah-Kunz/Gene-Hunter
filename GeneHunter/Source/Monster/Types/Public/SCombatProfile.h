// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Type.h"
#include "TypeArray1D.h"
#include "CoreMinimal.h"
#include "CombatAnalysisMode.h"
#include "Widgets/SCompoundWidget.h"

/**
 * SCompoundWidget that draws a UType "name plate".
 */
class TYPES_API SCombatProfile : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SCombatProfile)
		:
	_Types({})
	, _Width(80)
	, _Height(20)
	, _CornerRadius(4)
	, _TypesPerRow(3)
	, _CombatAnalysisMode(ECombatAnalysisMode::Both)
		{}

	SLATE_ARGUMENT(TArray<UType*>, Types)
	SLATE_ARGUMENT(float, Width)
	SLATE_ARGUMENT(float, Height)
	SLATE_ARGUMENT(float, CornerRadius)
	SLATE_ARGUMENT(int, TypesPerRow)
	SLATE_ARGUMENT(ECombatAnalysisMode, CombatAnalysisMode)
	
	SLATE_END_ARGS()

public:

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SVerticalBox> MakeSlate(const FArguments& InArgs);

	void MakeCombatProfile(const FArguments& InArgs, const TSharedRef<SVerticalBox>& VerticalBox, const bool bAtk,
	                       const TArray<UType*>& AllTypes);

	/**
	 * Draws a single row.
	 */
	virtual TSharedRef<SWidget> MakeTypeRowWidget(const FArguments& InArgs, TArray<FTypeArray1D>& Analysis, 
    		const int ArrayIndex);

	TSharedRef<SWidget> DrawNoCombatProfile() const;
};