USTRUCT(BlueprintType)
struct FTypeAdvantageStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float modifier = 1.0f;

    /**~
    * This UObject pointer is not accessible to Blueprint Graphs, but
    * is visible to UE4's reflection, smart pointer, and garbage collection
    * systems.
    */
    UPROPERTY()
    UObject* SafeObjectPointer;
};