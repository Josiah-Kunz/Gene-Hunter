﻿#include "AffinitiesComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Images/SImage.h"
#include "Types/SlateStructs.h"
#include "EditorStyleSet.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "TypeUtilities.h"
#include "WidgetFunctionLibrary.h"
#include "Widgets/Colors/SColorBlock.h"

#define LOCTEXT_NAMESPACE "AffinitiesComponentDrawer"

#pragma region Boilerplate

TSharedRef<IDetailCustomization> AffinitiesComponentDrawer::MakeInstance()
{
	return MakeShareable(new AffinitiesComponentDrawer);
}

void AffinitiesComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	AffinitiesComponent = GetAffinitiesComponent(DetailBuilder);

	// Hide original drawer
	const TSharedRef<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(
		GET_MEMBER_NAME_CHECKED(UAffinitiesComponent, Affinities));
	PropertyHandle->MarkHiddenByCustomization();

	// Customize categories
	CustomizeAffinitiesCategory(DetailBuilder, PropertyHandle);
	CustomizeCombatProfileCategories(DetailBuilder, PropertyHandle);
}

#pragma endregion

#pragma region Affinities category customization functions

void AffinitiesComponentDrawer::CustomizeAffinitiesCategory(IDetailLayoutBuilder& DetailBuilder,
	const TSharedRef<IPropertyHandle> PropertyHandle)
{
	// Get category
	IDetailCategoryBuilder& Category = GetCategory(DetailBuilder,
		PropertyHandle->GetDefaultCategoryName().ToString());

	// Details
	CustomizeMaxUsableAffinities(DetailBuilder, Category);
	CustomizeAffinities(DetailBuilder, Category);
}

void AffinitiesComponentDrawer::CustomizeMaxUsableAffinities(IDetailLayoutBuilder& DetailBuilder,
															 IDetailCategoryBuilder& Category)
{
	Category.AddCustomRow(LOCTEXT("KeyWord", "MaxUsableAffinities"))
	.NameContent()[
		SNew(STextBlock)
		.Text(FText::FromString("Max Usable Affinities"))
		.ToolTipText(FText::FromString("The number of Types this Monster may have. For example, if this is 2, this Monster may be single or dual-typed."))
	]
	.ValueContent()[
		SNew(SEditableTextBox)
		.Text(FText::FromString(FString::Printf(TEXT("%i"), AffinitiesComponent->GetMaxUsableAffinities())))
		.OnTextCommitted_Lambda([this, &DetailBuilder](const FText& InText, const ETextCommit::Type InTextCommit)
		{
			AffinitiesComponent->SetMaxUsableAffinities(FCString::Atoi(*InText.ToString()));
			SaveAndRefresh(DetailBuilder);
		})
	]
	.OverrideResetToDefault(
		FResetToDefaultOverride::Create( 
		TAttribute<bool>::CreateLambda([this]() 
			{ 
				return AffinitiesComponent->GetMaxUsableAffinities() != 2;
			}), 
			FSimpleDelegate::CreateLambda(
			[this, &DetailBuilder]()
			{
				AffinitiesComponent->SetMaxUsableAffinities(2);
				SaveAndRefresh(DetailBuilder);
			})
		)
	)
	;
}

void AffinitiesComponentDrawer::CustomizeAffinities(IDetailLayoutBuilder& DetailBuilder,
	IDetailCategoryBuilder& Category)
{

	// Draw 'em
	for(FAffinity& Affinity : AffinitiesComponent->Affinities)
		DrawAffinity(DetailBuilder, Category, Affinity);

	// Draw +/- for modifying array
	DrawArrayMutator(DetailBuilder, Category);
}

void AffinitiesComponentDrawer::DrawAffinity(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
	FAffinity& Affinity)
{
	// Get useful variables
	TypeNames = GetTypeNames();
	const TSharedPtr<FString> InitialName =
		Affinity.Type == nullptr ?
		TypeNames[0] :
		MakeShared<FString>(Affinity.Type->GetName());
	
	// Draw slate
	Category.AddCustomRow(LOCTEXT("KeyWord", "Affinity"))
	.NameContent()
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)

		// ComboBox
		+SOverlay::Slot()[
			SNew(STextComboBox)
				.OptionsSource(&TypeNames)
				.InitiallySelectedItem(InitialName)
				.OnSelectionChanged_Lambda(OnComboBoxChanged(DetailBuilder, Affinity))
				//.OnComboBoxOpening_Lambda([](){}) // Something is fishy here...
		]
		.HAlign(HAlign_Fill)
		.Padding(28, 0, 0, 0)

		// Lock
		+SOverlay::Slot()[
			SNew(SButton)
			.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
			.OnClicked_Lambda([this, &DetailBuilder, &Affinity]() -> FReply
			{
				// Set state
				Affinity.SetLockedState(!Affinity.IsLocked());

				// Save + return
				SaveAndRefresh(DetailBuilder);
				return FReply::Handled();
			})
			.IsEnabled_Lambda([this, &Affinity]()
			{
				// If already locked, we always want to be able to unlock it
				if (Affinity.IsLocked())
					return true;

				// See if we can otherwise modify it
				return CanModifyAffinity(Affinity);
			})
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
	]
	.ValueContent()
	[
		AffinityValueWidget(DetailBuilder, Affinity).ToSharedRef()
	]
	.OverrideResetToDefault(FResetToDefaultOverride::Create( 
		TAttribute<bool>::CreateLambda([&Affinity]() 
			{ 
				return Affinity.GetMaxPoints() != 3 || Affinity.GetCurrentPoints() != 0;
			}), 
			CreateResetDelegate(DetailBuilder, Affinity)
		)
	)
	;
}

void AffinitiesComponentDrawer::DrawArrayMutator(IDetailLayoutBuilder& DetailBuilder,
	IDetailCategoryBuilder& Category)
{
	Category.AddCustomRow(LOCTEXT("KeyWord", "Array Mutator"))
	.WholeRowContent()
	.HAlign(HAlign_Right)
	[
		SNew(SHorizontalBox)

		// Plus
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.OnClicked_Lambda([this, &DetailBuilder]() -> FReply
			{
				FAffinity NewAffinity = FAffinity{};
				NewAffinity.Type = AllTypes[0];
				AffinitiesComponent->Affinities.Add(NewAffinity);
				SaveAndRefresh(DetailBuilder);
				return FReply::Handled();
			})
			.ToolTipText(FText::FromString("Add an affinity to the array."))
			[
				SNew(SImage)
				.Image(FEditorStyle::GetBrush(TEXT("Icons.Plus")))
				.DesiredSizeOverride(FVector2D{16, 16})
			]
		]

		// Minus
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.OnClicked_Lambda([this, &DetailBuilder]() -> FReply
			{
				if (AffinitiesComponent->Affinities.Num() > 0)
				{
					AffinitiesComponent->Affinities.RemoveAt(AffinitiesComponent->Affinities.Num() - 1);
					SaveAndRefresh(DetailBuilder);
				}
				return FReply::Handled();
			})
			.IsEnabled_Lambda([this]()
			{
				return AffinitiesComponent->Affinities.Num() > 1;
			})
			.ToolTipText(FText::FromString("Removes the last affinity from the array."))
			[
				SNew(SImage)
				.Image(FEditorStyle::GetBrush(TEXT("Icons.Minus")))
				.DesiredSizeOverride(FVector2D{16, 16})
			]
		]

		// Trash
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.OnClicked_Lambda([this, &DetailBuilder]() -> FReply
			{
				for(int i=AffinitiesComponent->Affinities.Num() - 1; i>0; i--)
					AffinitiesComponent->Affinities.RemoveAt(i);
				SaveAndRefresh(DetailBuilder);
				return FReply::Handled();
			})
			.IsEnabled_Lambda([this]()
			{
				return AffinitiesComponent->Affinities.Num() > 1;
			})
			.ToolTipText(FText::FromString("Remove all affinities except the first one."))
			[
				SNew(SImage)
				.Image(FEditorStyle::GetBrush("FoliageEditMode.Remove"))
				.DesiredSizeOverride(FVector2D{16, 16})
			]
		]
	]
	;
}

void AffinitiesComponentDrawer::CustomizeCombatProfileCategories(IDetailLayoutBuilder& DetailBuilder,
	const TSharedRef<IPropertyHandle> PropertyHandle)
{
	// Get categories
	IDetailCategoryBuilder& AtkCategory = GetCategory(DetailBuilder, "Attack Profile");
	IDetailCategoryBuilder& DefCategory = GetCategory(DetailBuilder, "Defense Profile");
	

	// Analyze the types' combat
	TArray<UType*> AffinityTypes;
	AffinitiesComponent->GetTypes(AffinityTypes);

	// Draw profiles
	DrawCombatProfile(DetailBuilder, AtkCategory, AffinityTypes, true);
	DrawCombatProfile(DetailBuilder, DefCategory, AffinityTypes, false);
	
}

void AffinitiesComponentDrawer::DrawCombatProfile(IDetailLayoutBuilder& DetailBuilder,
	IDetailCategoryBuilder& Category, TArray<UType*>& AffinityTypes, const bool bAtk)
{

	// Iterate though ranges
	bool bDrewOne = false;
	for(const TPair<FFloatRange, FString>& RangeLabelPair : UTypeUtilities::EffectivenessLabels(bAtk))
	{

		// Do the analysis
		TArray<FTypeArray1D> TypeCombinations, Analysis;
		UTypeUtilities::GetAllTypeCombinations(AllTypes, 1, TypeCombinations);
		UTypeUtilities::Analyze(
			AffinityTypes,
			TypeCombinations,
			RangeLabelPair.Key,
			Analysis,
			EAttackModifierMode::Coverage,
			bAtk
		);

		// If no types, skip
		if (Analysis.Num() == 0)
			continue;
		bDrewOne = true;

		// Header
		Category.AddCustomRow(LOCTEXT("KeyWord", "Profile Header"))
		.WholeRowContent()
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(RangeLabelPair.Value))
			.Font(FEditorStyle::GetFontStyle("BoldFont"))
			.TextStyle(FEditorStyle::Get(), "Menu.Heading")
			.ColorAndOpacity(FLinearColor::White)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ShadowOffset(FVector2D{1, 1})
		]
		;

		// Types slate
		constexpr int TypesPerRow = 3;
		for(int i=0; i<Analysis.Num(); i+=TypesPerRow)
		{

			// Create container
			TSharedPtr<SHorizontalBox> Container = SNew(SHorizontalBox);

			// Add stuff
			for(int j=0; j<TypesPerRow; j++)
			{	
				Container->AddSlot()
				.AutoWidth()
				.Padding(2)
				[
					MakeTypeRowWidget(Analysis, i+j)
				]
				;
			}
			
			Category.AddCustomRow(LOCTEXT("KeyWord", "Type Row"))
			.WholeRowContent()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				Container.ToSharedRef()
			]
			;
		}
	}

	// Didn't draw any =(
	if (!bDrewOne)
		NoCombatProfile(Category);
}

TSharedRef<SWidget> AffinitiesComponentDrawer::MakeTypeRowWidget(TArray<FTypeArray1D>& Analysis, const int ArrayIndex,
	const float Width, const float Height, const float CornerRadius)
{

	// Check within array range
	if (ArrayIndex >= Analysis.Num())
	{
		return SNew(SOverlay);
	}

	// Get Type (for readability)
	UType* Type = Analysis[ArrayIndex].Array[0];

	// Build fo rill
	return SNew(SOverlay)

		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SColorBlock)
			.Size(FVector2D{Width, Height})
			.Color(Type->Colors[0])
			.CornerRadius(FVector4{CornerRadius, CornerRadius, CornerRadius, CornerRadius})
			.ToolTipText(Type->SupportingText.Description)
		]

		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Type->GetName()))
			.ToolTipText(Type->SupportingText.Description)
			.Font(FEditorStyle::GetFontStyle(TEXT("BoldFont")))
			.ColorAndOpacity(UWidgetFunctionLibrary::CorrespondingTextColor(Type->Colors[0]))
			.ShadowColorAndOpacity(UWidgetFunctionLibrary::CorrespondingOutlineColor(Type->Colors[0]))
			.ShadowOffset(FVector2D{1, 1})
			.Justification(ETextJustify::Center)
		]
	;
}

void AffinitiesComponentDrawer::NoCombatProfile(IDetailCategoryBuilder& Category)
{
	Category.AddCustomRow(LOCTEXT("KeyWord", "AttackProfile Header"))
		.WholeRowContent()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString("All Neutral"))
			.Font(FEditorStyle::GetFontStyle("BoldFont"))
			.TextStyle(FEditorStyle::Get(), "Menu.Heading")
			.ColorAndOpacity(FLinearColor::White)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ShadowOffset(FVector2D{1, 1})
		]
		;
}

void AffinitiesComponentDrawer::SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const
{
	UKismetSystemLibrary::TransactObject(AffinitiesComponent);
	DetailBuilder.ForceRefreshDetails();
}

bool AffinitiesComponentDrawer::UserCommitted(const ETextCommit::Type CommitType)
{
	return CommitType == ETextCommit::Type::OnEnter || CommitType == ETextCommit::Type::OnUserMovedFocus;
}

UAffinitiesComponent* AffinitiesComponentDrawer::GetAffinitiesComponent(const IDetailLayoutBuilder& DetailBuilder)
{
	// Get object from array
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);
	if (ObjectsToEdit.Num() == 0) return nullptr;
	
	// Object guard
	const TWeakObjectPtr<UObject> Object = ObjectsToEdit[0];
	if (!Object.IsValid()) return nullptr;

	// Get
	UAffinitiesComponent* Ret = Cast<UAffinitiesComponent>(Object.Get());

	// Guard again
	if (!Ret) return nullptr;

	// Return
	return Ret;
}

IDetailCategoryBuilder& AffinitiesComponentDrawer::GetCategory(IDetailLayoutBuilder& DetailBuilder,
	const FString CategoryName)
{
	return DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);
}

TArray<TSharedPtr<UType*, ESPMode::ThreadSafe>> AffinitiesComponentDrawer::GetTypes() const
{
	TArray<UType*> Types;
	UType::GetAllTypes(Types, {});
	TArray<TSharedPtr<UType*, ESPMode::ThreadSafe>> Options = {};
	for(int i=0; i<Types.Num(); i++)
		Options.Add(MakeShared<UType*>(Types[i]));
	return Options;
}

TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> AffinitiesComponentDrawer::GetTypeNames()
{
	UType::GetAllTypes(AllTypes, {});
	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> Options = {};
	for(int i=0; i<AllTypes.Num(); i++)
		Options.Add(MakeShared<FString>(AllTypes[i]->GetName()));
	return Options;
}

TSharedPtr<SHorizontalBox> AffinitiesComponentDrawer::AffinityValueWidget(IDetailLayoutBuilder& DetailBuilder,
	FAffinity& Affinity) const
{
	// Set up variables
	//TSharedPtr<SCanvas> Ret = SNew(SCanvas);
	TSharedPtr<SHorizontalBox> Ret = SNew(SHorizontalBox);
	constexpr float Padding = 2;
	constexpr float CircleSizeEmpty = 20;
	constexpr float PMSize = 12;

	// Minus
	Ret->AddSlot()[
		SNew(SButton)
		.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
		.OnClicked_Lambda([this, &DetailBuilder, &Affinity]() -> FReply
		{
			if (Affinity.GetMaxPoints() > 1)
			{
				Affinity.SetMaxPoints(Affinity.GetMaxPoints() - 1);
				SaveAndRefresh(DetailBuilder);
			} 
			return FReply::Handled();
		})
		.ToolTipText(FText::FromString("Decrease max affinity points by 1."))
		[
			SNew(SImage)
			.Image( FEditorStyle::GetBrush(TEXT("Icons.Minus")))
			.DesiredSizeOverride(FVector2D{PMSize, PMSize})
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	]
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.SizeParam(FAuto{})
	.Padding(Padding)
	;

	// Circles
	for(int i=0; i<Affinity.GetMaxPoints(); i++)
	{
		const bool bFilled = i < Affinity.GetCurrentPoints();
		const int CurrentPoints = Affinity.GetCurrentPoints();
		Ret->AddSlot()[

			SNew(SButton)
			.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
			.ToolTipText(FText::FromString("Click to set this as the current number of affinity points."))
			.OnClicked_Lambda([this, &DetailBuilder, &Affinity, i, CurrentPoints]() -> FReply
			{

				// If at exactly (1), the only way to remove it is to click it
				if (CurrentPoints == i+1)
					Affinity.SetCurrentPoints(CurrentPoints - 1);
				else 
					Affinity.SetCurrentPoints(i+1);
				SaveAndRefresh(DetailBuilder);
				return FReply::Handled();
			})
			[
				SNew(SOverlay)

				+SOverlay::Slot()[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("TutorialLaunch.Circle"))
					.DesiredSizeOverride(FVector2D{CircleSizeEmpty, CircleSizeEmpty})
					.ColorAndOpacity(FLinearColor{0.2f, 0.2f, 0.2f})
					]

				+SOverlay::Slot()[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("Sequencer.KeyCircle"))
					.ColorAndOpacity(
						bFilled ?
						Affinity.Type->Colors[0] :
						FLinearColor{0, 0, 0, 0}
						)
					].Padding(4)
			]
		]
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.SizeParam(FAuto{})
		.Padding(Padding)
	;
	}

	// Plus
	Ret->AddSlot()[
		SNew(SButton)
		.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
		.OnClicked_Lambda([this, &DetailBuilder, &Affinity]() -> FReply
		{
			Affinity.SetMaxPoints(Affinity.GetMaxPoints()+1);
			SaveAndRefresh(DetailBuilder);
			return FReply::Handled();
		})
		.ToolTipText(FText::FromString("Increase max affinity points by 1."))
		[
			SNew(SImage)
			.Image( FEditorStyle::GetBrush(TEXT("Icons.Plus")))
			.DesiredSizeOverride(FVector2D{PMSize, PMSize})
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	]
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.SizeParam(FAuto{})
	.Padding(Padding)
	;

	// Enabled
	Ret->SetEnabled(CanModifyAffinity(Affinity));
	
	// Return
	return Ret;
}

UType* AffinitiesComponentDrawer::GetTypeByName(const FString* TypeName)
{
	for(UType* Type : AllTypes)
		if (Type->GetName().Equals(*TypeName))
			return Type;
	return nullptr;
}

TFunction<void(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)> AffinitiesComponentDrawer::
OnComboBoxChanged(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity)
{
	return [this, &DetailBuilder, &Affinity](TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)
	{
		if (!Selection.IsValid())
			return;

		UType* SelectedType = GetTypeByName(Selection.Get());
		if (SelectedType != nullptr)
		{
			Affinity.Type = SelectedType;
			//UKismetSystemLibrary::TransactObject(AffinitiesComponent);
			SaveAndRefresh(DetailBuilder);
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Selected Type is nullptr in AffinitiesComponentDrawer! Surely this is an error. Reverting to default value."))
			if (AllTypes.Num() == 0)
				GetTypeNames();
			if (AllTypes.Num() > 0)
				Affinity.Type = AllTypes[0];
		}
	};
}

FSimpleDelegate AffinitiesComponentDrawer::CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder,
	FAffinity& Affinity) const
{
	return FSimpleDelegate::CreateLambda(
		[this, &DetailBuilder, &Affinity]()
		{
			Affinity.SetLockedState(false);
			Affinity.SetMaxPoints(3);
			Affinity.SetCurrentPoints(0);
			SaveAndRefresh(DetailBuilder);
		}
	);
}

bool AffinitiesComponentDrawer::CanModifyAffinity(const FAffinity& Affinity) const
{
	if (AffinitiesComponent->CanChooseNewType())
		return true;
	return Affinity.GetCurrentPoints() > 0;
}

#undef LOCTEXT_NAMESPACE
