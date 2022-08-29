// Fill out your copyright notice in the Description page of Project Settings.


#include "SAffinityNameContent.h"

#include "EditorStyleSet.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAffinityNameContent::Construct(const FArguments& InArgs)
{
UE_LOG(LogTemp, Warning, TEXT("Is lock enabled for Type %s? %s "),
	*InArgs._Affinity.Type->GetName(),
	(InArgs._IsLockEnabled.Get() ? *FString("Yes") : *FString("No"))
	)
	// Ensure affinity type isn't null
	const FAffinity& Affinity = InArgs._Affinity;
	check(Affinity.Type)
	
	// Get name variables
	TypeNames = GetTypeNames();
	const TSharedPtr<FString> InitialName =
		Affinity.Type == nullptr ?
		TypeNames[0] :
		MakeShared<FString>(Affinity.Type->GetName());

	ChildSlot
	[
	SNew(SOverlay)

	// ComboBox
	+SOverlay::Slot()[
		SNew(STextComboBox)
			.OptionsSource(&TypeNames)
			.InitiallySelectedItem(InitialName)
			.OnSelectionChanged_Lambda(InArgs._OnComboBoxChanged.Get())
			.OnComboBoxOpening_Lambda(InArgs._OnComboBoxOpening.Get()) // Something is fishy here...
	]
	.HAlign(HAlign_Fill)
	.Padding(28, 0, 0, 0) // For the lock

	// Lock
	+SOverlay::Slot()[
		SNew(SButton)
		.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
		.OnClicked_Lambda(InArgs._OnLockClicked.Get())
		.IsEnabled(InArgs._IsLockEnabled.Get())
		.ToolTipText(
			Affinity.IsLocked() ?
			FText::FromString("Unlock this affinity. If locked, this affinity is required and cannot be changed in-game. Current state is [LOCKED].") :
			FText::FromString("Lock this affinity. If locked, this affinity is required and cannot be changed in-game. Current state is [UNLOCKED].")
		)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(
				Affinity.IsLocked() ?
				TEXT("Sequencer.LockSequence") :
				TEXT("Sequencer.UnlockSequence")
			))
			.DesiredSizeOverride(FVector2D{16, 16})
		]
		.HAlign(HAlign_Left)
	]
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	];
	
}

TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> SAffinityNameContent::GetTypeNames() const
{
	TArray<UType*> AllTypes;
	UType::GetAllTypes(AllTypes, {});
	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> Options = {};
	for(int i=0; i<AllTypes.Num(); i++)
		Options.Add(MakeShared<FString>(AllTypes[i]->GetName()));
	return Options;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
