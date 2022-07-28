#include "EditorBackgroundParent.h"
#include "Blueprint/WidgetTree.h"
#include "BPLibraries/Public/WidgetFunctionLibrary.h"
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
	ClickOffButton = Cast<UButton>(UWidgetFunctionLibrary::GetChildOfType(this, UButton::StaticClass()));

	return bRet;
}

