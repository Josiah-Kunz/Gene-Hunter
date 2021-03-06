
#include "EditorBackgroundParent.h"
#include "GeneHunter/GeneHunterBPLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/Canvas.h"

void UEditorBackgroundParent::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (!ClickOffButton)
		Initialize();
	if (ClickOffButton)
		Cast< UCanvasPanelSlot >(ClickOffButton->Slot)->SetOffsets(FMargin(0, 0, Width, 0));
}

bool UEditorBackgroundParent::Initialize()
{
	// Base class return value
	const bool bRet = Super::Initialize();

	// Auto-assign width
	Width = 480;

	// Auto-assign ClickOffButton
	ClickOffButton = Cast<UButton>(UGeneHunterBPLibrary::GetChildOfType(this, UButton::StaticClass()));

	return bRet;
}

