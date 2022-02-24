


#include "TypeComboBox.h"

TSharedRef<SWidget> UTypeComboBox::RebuildWidget()
{
	TSharedRef<SWidget> Ret = Super::RebuildWidget();
	UGeneHunterBPLibrary::GetAllTypes(Types, {});
	Options = {MakeShared<FString>(TEXT("<None>"))};
	for(int i=0; i<Types.Num(); i++)
		Options.Add(MakeShared<FString>(Types[i]->GetName()));
	SetSelectedIndex(0);
	return Ret;
}

UType* UTypeComboBox::GetType(int index)
{
	if (index <= 0 || Types.Num() < index)
		return nullptr;
	return Types[index - 1];
}

void UTypeComboBox::SetForegroundColor(FLinearColor Color)
{
	ForegroundColor = Color;
}

void UTypeComboBox::SetBackgroundColor(const FLinearColor NormalForeground, const FLinearColor HoveredForeground, const FLinearColor PressedForeground)
{
	FButtonStyle ButtonStyle = this->WidgetStyle.ComboButtonStyle.ButtonStyle;
	ButtonStyle.NormalForeground = NormalForeground;
	ButtonStyle.HoveredForeground = HoveredForeground;
	ButtonStyle.PressedForeground = PressedForeground;
	this->WidgetStyle.ComboButtonStyle.SetButtonStyle(ButtonStyle);
}
