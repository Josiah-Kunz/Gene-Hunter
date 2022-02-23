

#pragma once

#include "GeneHunterBPLibrary.h"
#include "CoreMinimal.h"
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
};
