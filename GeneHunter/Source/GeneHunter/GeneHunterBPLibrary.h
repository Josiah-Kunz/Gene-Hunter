

#pragma once

#include "CoreMinimal.h"
#include "K2Node_GetDataTableRow.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"
#include "GeneHunterBPLibrary.generated.h"


/**
 * 
 */
UCLASS()
class GENEHUNTER_API UGeneHunterBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static float SquareNumber(const float In);

	UFUNCTION(BlueprintCallable)
	static void WriteToDataTableZZZ(const UDataTable* DataTable, const FString RowName);
};
