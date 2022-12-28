UENUM(BlueprintType)
enum class EStatModifierTrigger : uint8
{
	None				UMETA(Tooltip="No modification (this FEffect does nothing)."),
	RecalculateStats	UMETA(Tooltip="Modification triggered via UStatsComponent::RecalculateStats"),
	ModifyStats			UMETA(Tooltip="Modification triggered via UStatsComponent::ModifyStatsInternal"),
	Both				UMETA(Tooltip="Modification triggered via RecalculateStats and ModifyStats."),
};