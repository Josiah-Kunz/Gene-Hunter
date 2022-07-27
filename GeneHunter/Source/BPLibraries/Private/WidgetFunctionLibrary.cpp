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




