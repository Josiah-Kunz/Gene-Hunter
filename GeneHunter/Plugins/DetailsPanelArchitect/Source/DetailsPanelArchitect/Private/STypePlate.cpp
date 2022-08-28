// Fill out your copyright notice in the Description page of Project Settings.


#include "STypePlate.h"

#include "SlateOptMacros.h"
#include "WidgetFunctionLibrary.h"
#include "Widgets/Colors/SColorBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STypePlate::Construct(const FArguments& InArgs)
{
	// Ensure affinity type isn't null
	TSharedRef<SOverlay> TypePlate = SNew(SOverlay);
	if (InArgs._Type == nullptr)
		TypePlate = MakeSlate(
			InArgs,
			FLinearColor::Gray,
			FText::FromString("NULL"),
			FText::FromString("No Type was selected! Was it not set in the code?")
		);
	else
		TypePlate = MakeSlate(
			InArgs,
			InArgs._Type->Colors[0],
			FText::FromString(InArgs._Type->GetName()),
			InArgs._Type->SupportingText.Description
		);
	ChildSlot
	[
		TypePlate
	];
	
}

TSharedRef<SOverlay> STypePlate::MakeSlate(const FArguments& InArgs, FLinearColor Color, FText Name, FText Description) const
{
	return SNew(SOverlay)

		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SColorBlock)
			.Size(FVector2D{InArgs._Width, InArgs._Height})
			.Color(Color)
			.CornerRadius(FVector4{
				InArgs._CornerRadius, InArgs._CornerRadius, InArgs._CornerRadius, InArgs._CornerRadius})
			.ToolTipText(Description)
		]

		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.Text(Name)
			.ToolTipText(Description)
			.Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
			.ColorAndOpacity(UWidgetFunctionLibrary::CorrespondingTextColor(Color))
			.ShadowColorAndOpacity(UWidgetFunctionLibrary::CorrespondingOutlineColor(Color))
			.ShadowOffset(FVector2D{1, 1})
			.Justification(ETextJustify::Center)
		]
	;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
