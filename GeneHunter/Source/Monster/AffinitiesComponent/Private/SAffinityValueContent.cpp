// Fill out your copyright notice in the Description page of Project Settings.


#include "SAffinityValueContent.h"

#include "EditorStyleSet.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAffinityValueContent::Construct(const FArguments& InArgs)
{

	// Ensure affinity type isn't null
	if (InArgs._Affinity.Type == nullptr)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Affinity Type is null! Maybe you forgot to add it when constructing the slate (i.e., \".Affinity(whatever)\")."))
		return;
	}
	
	ChildSlot
	[
		AffinityValueSlate(InArgs)->AsShared()
	];
	
}

TSharedPtr<SHorizontalBox> SAffinityValueContent::AffinityValueSlate(const FArguments& InArgs) const
{
	
	// Set up variables
	TSharedPtr<SHorizontalBox> Ret = SNew(SHorizontalBox);

	// Minus
	Ret->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.SizeParam(FAuto{})
		.Padding(InArgs._CirclePadding)
		[
			SNew(SButton)
			.ButtonStyle( FAppStyle::Get(), "NoBorder" )
			.OnClicked_Lambda(InArgs._OnMinusClicked.Get())
			.ToolTipText(InArgs._MinusToolTipText)
			[
				SNew(SImage)
				.Image( FAppStyle::GetBrush(TEXT("Icons.Minus")))
				.DesiredSizeOverride(FVector2D{InArgs._PlusMinusSize, InArgs._PlusMinusSize})
			]
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
		]
	;

	// Circles
	for(int i=0; i<InArgs._Affinity.GetMaxPoints(); i++)
	{
		const int CurrentPoints = InArgs._Affinity.GetCurrentPoints();
		const bool bFilled = i < CurrentPoints;
		Ret->AddSlot()[

			SNew(SButton)
			.ButtonStyle( FAppStyle::Get(), "NoBorder" )
			.ToolTipText(InArgs._CircleToolTipText)
			//.OnClicked_Lambda(InArgs._OnCircleClicked.Get())
			.OnClicked_Lambda([InArgs, i, CurrentPoints]()
			{
				return InArgs._OnCircleClicked.Get().operator()(i, CurrentPoints);
			})
			[
				SNew(SOverlay)

				+SOverlay::Slot()[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("TutorialLaunch.Circle"))
					.DesiredSizeOverride(FVector2D{InArgs._CircleSizeEmpty, InArgs._CircleSizeEmpty})
					.ColorAndOpacity(FLinearColor{0.2f, 0.2f, 0.2f})
					]

				+SOverlay::Slot()[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("Sequencer.KeyCircle"))
					.ColorAndOpacity(
						bFilled ?
						InArgs._Affinity.Type->Colors[0] :
						FLinearColor{0, 0, 0, 0}
						)
					].Padding(InArgs._CircleSizeEmpty - InArgs._CircleSizeFilled)
			]
		]
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.SizeParam(FAuto{})
		.Padding(InArgs._CirclePadding)
	;
	}

	// Plus
	Ret->AddSlot()[
		SNew(SButton)
		.ButtonStyle( FAppStyle::Get(), "NoBorder" )
		.OnClicked_Lambda(InArgs._OnPlusClicked.Get())
		.ToolTipText(InArgs._PlusToolTipText)
		[
			SNew(SImage)
			.Image( FAppStyle::GetBrush(TEXT("Icons.Plus")))
			.DesiredSizeOverride(FVector2D{InArgs._PlusMinusSize, InArgs._PlusMinusSize})
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	]
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.SizeParam(FAuto{})
	.Padding(InArgs._CirclePadding)
	;
	
	// Enabled
	Ret->SetEnabled(InArgs._Enabled.Get().operator()());
	
	// Return
	return Ret;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
