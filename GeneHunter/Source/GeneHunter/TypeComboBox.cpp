


#include "TypeComboBox.h"

TSharedRef<SWidget> UTypeComboBox::RebuildWidget()
{
	TSharedRef<SWidget> Ret = Super::RebuildWidget();
	TArray<UType*> Types;
	UGeneHunterBPLibrary::GetAllTypes(Types, {});
	Options = {MakeShared<FString>(TEXT("<None>"))};
	for(const UType* Type : Types)
		Options.Add(MakeShared<FString>(Type->GetName()));
	SetSelectedIndex(0);
	//ForegroundColor = FLinearColor(1, 1, 1);
	return Ret;
}


