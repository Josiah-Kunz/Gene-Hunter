


#include "TypeComboBox.h"

#include "Widgets/Input/STextComboBox.h"

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

UType* UTypeComboBox::GetSelectedType()
{
	return GetType(GetSelectedIndex());
}


UType* UTypeComboBox::GetType(int index)
{
	if (index <= 0 || Types.Num() < index)
		return nullptr;
	return Types[index - 1];
}
