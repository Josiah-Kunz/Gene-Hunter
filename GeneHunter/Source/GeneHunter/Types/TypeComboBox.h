

#pragma once

#include "../GeneHunterBPLibrary.h"
#include "CoreMinimal.h"
#include "Type.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "TypeComboBox.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UTypeComboBox : public UComboBoxString
{
	GENERATED_BODY()
	
	/** Overrides */
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TArray<UType*> Types;
	
public:

	UFUNCTION(BlueprintCallable)
	UType* GetSelectedType();
	
	UFUNCTION(BlueprintCallable)
	UType* GetType(const int Index);
	
};
