#include "AffinitiesComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Images/SImage.h"
#include "EditorStyleSet.h"
#include "SAffinityNameContent.h"
#include "SAffinityValueContent.h"
#include "SCombatProfile.h"
#include "STypePlate.h"
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

	Category.AddCustomRow(LOCTEXT("KeyWord", "Affinity"))

	// Name
	.NameContent()
	.HAlign(HAlign_Fill)
	[
		SNew(SAffinityNameContent)
		.Affinity(Affinity)
		.IsLockEnabled([this, &Affinity]()
			{
				// If already locked, we always want to be able to unlock it
				if (Affinity.IsLocked())
					return true;

				// See if we can otherwise modify it
				return CanModifyAffinity(Affinity);
			})
		.OnLockClicked([this, &DetailBuilder, &Affinity]() -> FReply
			{
				// Set state
				Affinity.SetLockedState(!Affinity.IsLocked());

				// Save + return
				SaveAndRefresh(DetailBuilder);
				return FReply::Handled();
			})
			
		.OnComboBoxChanged(OnComboBoxChanged(DetailBuilder, Affinity))
		//.OnComboBoxOpening([](){}) // Something is fishy here...
	]

	// Value
	.ValueContent()
	[
		SNew(SAffinityValueContent)
		.Affinity(Affinity)
		.OnMinusClicked([this, &DetailBuilder, &Affinity]() -> FReply
		{
			if (Affinity.GetMaxPoints() > 1)
			{
				Affinity.SetMaxPoints(Affinity.GetMaxPoints() - 1);
				SaveAndRefresh(DetailBuilder);
			} 
			return FReply::Handled();
		})
		.OnCircleClicked([this, &DetailBuilder, &Affinity](const int AffinityIndex, const int CurrentPoints) -> FReply
		{

			// If at exactly (1), the only way to remove it is to click it
			if (CurrentPoints == AffinityIndex+1)
				Affinity.SetCurrentPoints(CurrentPoints - 1);
			else 
				Affinity.SetCurrentPoints(AffinityIndex+1);
			SaveAndRefresh(DetailBuilder);
			return FReply::Handled();
		})
		.OnPlusClicked([this, &DetailBuilder, &Affinity]() -> FReply
		{
			Affinity.SetMaxPoints(Affinity.GetMaxPoints() + 1);
			SaveAndRefresh(DetailBuilder);
			return FReply::Handled();
		})
	]

	// Reset
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
				NewAffinity.Type = GetAllTypes()[0];
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

	Category.AddCustomRow(LOCTEXT("KeyWord", "Profile"))
	.WholeRowContent()
	.VAlign(VAlign_Center)
	[
		SNew(SCombatProfile)
			.Types(AffinityTypes)
			.CombatAnalysisMode(bAtk ? ECombatAnalysisMode::Attack : ECombatAnalysisMode::Defense)
	];
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
	const FString CategoryName) const
{
	return DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);
}

TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> AffinitiesComponentDrawer::GetTypeNames()
{
	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> Options = {};
	for(int i=0; i<GetAllTypes().Num(); i++)
		Options.Add(MakeShared<FString>(GetAllTypes()[i]->GetName()));
	return Options;
}

TArray<UType*> AffinitiesComponentDrawer::GetAllTypes()
{
	if (AllTypes.Num() == 0)
		UType::GetAllTypes(AllTypes);
	return AllTypes;
}

UType* AffinitiesComponentDrawer::GetTypeByName(const FString* TypeName)
{
	for(UType* Type : GetAllTypes())
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
			SaveAndRefresh(DetailBuilder);
		} else
		{
			UE_LOG(LogTemp, Warning,
				TEXT("Selected Type %s is nullptr in AffinitiesComponentDrawer! Surely this is an error. Reverting to default value."),
				Selection.Get()
			)
			if (GetAllTypes().Num() == 0)
				GetTypeNames();
			if (GetAllTypes().Num() > 0)
				Affinity.Type = GetAllTypes()[0];
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
