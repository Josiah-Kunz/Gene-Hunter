#include "WidgetFunctionLibrary.h"

void UWidgetFunctionLibrary::ClearChildrenExcept(UPanelWidget* Widget, const TArray<UWidget*> Exclude)
{
	for(int i=Widget->GetChildrenCount() - 1; i>=0; i--)
	{
		if (!Exclude.Contains(Widget->GetChildAt(i)))
			Widget->RemoveChildAt(i);
	}
}

UWidget* UWidgetFunctionLibrary::Duplicate(const UWidget* Original)
{
	return DuplicateObject(Original, Original->GetOuter());
}

UWidget* UWidgetFunctionLibrary::GetChildOfType(const UUserWidget* Parent, const TSubclassOf<UWidget> WidgetClass)
{
	TArray<UWidget*> Children;
	Parent->WidgetTree->GetAllWidgets(Children);
	for(UWidget* Child : Children)
	{
		if(Child->IsA(WidgetClass))
			return Child;
	}
	return nullptr;
}

FLinearColor UWidgetFunctionLibrary::CorrespondingTextColor(const FLinearColor& Color)
{
	if (Color.R + Color.G + Color.B > 1.5f)
		return FLinearColor::Black;
	return FLinearColor::White;
}

FLinearColor UWidgetFunctionLibrary::CorrespondingOutlineColor(const FLinearColor& Color)
{
	if (Color.R + Color.G + Color.B > 1.5f)
		return FLinearColor::White;
	return FLinearColor::Black;
}


