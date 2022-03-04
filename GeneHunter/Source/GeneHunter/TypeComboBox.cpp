


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


UType* UTypeComboBox::GetType(const int Index)
{
	if (Index <= 0 || Types.Num() < Index)
		return nullptr;
	return Types[Index - 1];
}
