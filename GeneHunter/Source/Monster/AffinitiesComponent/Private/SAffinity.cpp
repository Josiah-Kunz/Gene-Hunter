// Fill out your copyright notice in the Description page of Project Settings.


#include "SAffinity.h"


#include "SAffinityNameContent.h"
#include "SAffinityValueContent.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAffinity::Construct(const FArguments& InArgs)
{
	// Ensure affinity type isn't null
	check(InArgs._Affinity.Type)

	// Instead of always typing, e.g., ".IsLockEnabled(InArgs._IsLockEnabled)" you can just type LAZY_SET(IsLockEnabled)
#define LAZY_SET(Attribute) \
.##Attribute##(InArgs._##Attribute##)
	
	ChildSlot
	[
		SNew(SHorizontalBox)

		// Name
		+SHorizontalBox::Slot()[
			SNew(SAffinityNameContent)
			LAZY_SET(Affinity)
			LAZY_SET(IsLockEnabled)
			LAZY_SET(OnLockClicked)
			LAZY_SET(OnComboBoxChanged)
			LAZY_SET(OnComboBoxOpening)
		]

		// Value
		+SHorizontalBox::Slot()[
			SNew(SAffinityValueContent)
			LAZY_SET(Affinity)
			LAZY_SET(CirclePadding)
			LAZY_SET(CircleSizeEmpty)
			LAZY_SET(CircleSizeFilled)
			LAZY_SET(PlusMinusSize)
			LAZY_SET(MinusToolTipText)
			LAZY_SET(PlusToolTipText)
			LAZY_SET(CircleToolTipText)
			LAZY_SET(OnMinusClicked)
			LAZY_SET(OnPlusClicked)
			LAZY_SET(OnCircleClicked)
			LAZY_SET(Enabled)
		]
			
	];
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
