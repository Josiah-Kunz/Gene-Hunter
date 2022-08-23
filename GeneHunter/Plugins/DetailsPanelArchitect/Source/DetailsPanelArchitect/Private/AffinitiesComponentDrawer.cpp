#define LOCTEXT_NAMESPACE "AffinitiesComponentDrawer"

#include "AffinitiesComponentDrawer.h"

#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Images/SImage.h"
#include "Types/SlateStructs.h"

#pragma region Boilerplate

TSharedRef<IDetailCustomization> AffinitiesComponentDrawer::MakeInstance()
{
	return MakeShareable(new AffinitiesComponentDrawer);
}

void AffinitiesComponentDrawer::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	// Get object
	AffinitiesComponent = GetAffinitiesComponent(DetailBuilder);

	// Details
	CustomizeAffinities(DetailBuilder);
}

#pragma endregion

void AffinitiesComponentDrawer::CustomizeAffinities(IDetailLayoutBuilder& DetailBuilder)
{

	// Get category
	const FString CategoryName = "Affinities";
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(
		FName(CategoryName),
		FText::FromString(CategoryName),
		ECategoryPriority::Important);

	for(FAffinity& Affinity : AffinitiesComponent->Affinities)
		DrawAffinity(DetailBuilder, Category, Affinity);
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

		SNew(STextComboBox)
			.OptionsSource(&TypeNames)
			.InitiallySelectedItem(InitialName)
			.OnSelectionChanged_Lambda(OnComboBoxChanged(Affinity))
			//.OnComboBoxOpening_Lambda([](){}) // Something is fishy here...
	]
	.ValueContent()
	[
		AffinityValueCanvas(DetailBuilder, Affinity).ToSharedRef()
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

const TArray<TSharedPtr<UType*, ESPMode::ThreadSafe>> AffinitiesComponentDrawer::GetTypes() const
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

TSharedPtr<SHorizontalBox> AffinitiesComponentDrawer::AffinityValueCanvas(IDetailLayoutBuilder& DetailBuilder,
	FAffinity& Affinity)
{
	// Set up variables
	//TSharedPtr<SCanvas> Ret = SNew(SCanvas);
	TSharedPtr<SHorizontalBox> Ret = SNew(SHorizontalBox);
	const float Padding = 2;
	const float CircleSizeEmpty = 20;
	const float CircleSizeFull = 16;
	const float PMSize = 12;

	// Minus
	Ret->AddSlot()[
		SNew(SButton)
		.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
		.OnClicked_Lambda([this, &DetailBuilder, &Affinity]() -> FReply
		{
			if (Affinity.MaxPoints > 1)
			{
				Affinity.MaxPoints--;
				Affinity.CurrentPoints = FMath::Min(Affinity.CurrentPoints, Affinity.MaxPoints);
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

	// Empty circles
	for(int i=0; i<Affinity.MaxPoints; i++)
	{
		const bool bFilled = i < Affinity.CurrentPoints;
		Ret->AddSlot()[

			SNew(SButton)
			.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
			.ToolTipText(FText::FromString("Click to set this as the current number of affinity points."))
			.OnClicked_Lambda([this, &DetailBuilder, &Affinity, i]() -> FReply
			{
				Affinity.CurrentPoints = i + 1;
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
			Affinity.MaxPoints++;
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
OnComboBoxChanged(FAffinity& Affinity)
{
	return [this, &Affinity](TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)
	{
		if (!Selection.IsValid())
			return;

		UType* SelectedType = GetTypeByName(Selection.Get());
		if (SelectedType != nullptr)
		{
			Affinity.Type = SelectedType;
			UKismetSystemLibrary::TransactObject(AffinitiesComponent);
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

#undef LOCTEXT_NAMESPACE
