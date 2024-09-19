#include "OverlapTracker.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Actor.h"

UOverlapTracker::UOverlapTracker(): CollisionComponent(nullptr)
{
    PrimaryComponentTick.bCanEverTick = false;
}

const TArray<AActor*>& UOverlapTracker::GetOverlappingActors() const
{
    return OverlappingActors;
}

void UOverlapTracker::GetOverlappingComponents(const TSubclassOf<UActorComponent> ComponentType, TArray<UActorComponent*>& Components)
{
    TArray<TSubclassOf<UActorComponent>> SupportedTypes;
    TrackedComponentInstances.GetKeys(SupportedTypes);
    if (SupportedTypes.Contains(ComponentType))
    {
        Components = TrackedComponentInstances[ComponentType];
    }
}

void UOverlapTracker::BeginPlay()
{
    Super::BeginPlay();

    // Bind the overlap events for the selected collision component
    BindOverlapEvents();
}

void UOverlapTracker::OnComponentCreated()
{
    Super::OnComponentCreated();

    // Bind overlap events if the component is set in the editor
    BindOverlapEvents();
}

void UOverlapTracker::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    Super::OnComponentDestroyed(bDestroyingHierarchy);

    // Unbind events to avoid issues when the component is destroyed
    UnbindOverlapEvents();
}

void UOverlapTracker::BindOverlapEvents()
{
    if (CollisionComponent)
    {
        // Ensure overlap events are enabled on the selected component
        CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
        CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

        // Bind overlap callbacks
        CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UOverlapTracker::OnBeginOverlap);
        CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UOverlapTracker::OnEndOverlap);
    }
}

void UOverlapTracker::UnbindOverlapEvents() const
{
    if (CollisionComponent)
    {
        // Unbind overlap callbacks to prevent issues when the component is replaced or destroyed
        CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
        CollisionComponent->OnComponentEndOverlap.RemoveAll(this);
    }
}

void UOverlapTracker::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                     bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {

        // Add to actor list
        OverlappingActors.AddUnique(OtherActor);

        // Add its tracked components
        for (UActorComponent* Component : OtherActor->GetComponents())
        {
            UClass* ComponentClass = Component->GetClass();
            if (TrackedComponents.Contains(ComponentClass))
            {
                TrackedComponentInstances.FindOrAdd(ComponentClass).Add(Component);
            }
        }
    }
}

void UOverlapTracker::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {

        // Remove components
        for (UActorComponent* Component : OtherActor->GetComponents())
        {
            UClass* ComponentClass = Component->GetClass();
            if (TrackedComponents.Contains(ComponentClass))
            {
                TrackedComponentInstances.Find(ComponentClass)->Remove(Component);
            }
        }

        // Remove actor
        OverlappingActors.Remove(OtherActor);
    }
}

#if WITH_EDITOR
void UOverlapTracker::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Check if the CollisionComponent was changed in the editor
    const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UOverlapTracker, CollisionComponent))
    {
        // Unbind events from the old component and bind to the new one
        UnbindOverlapEvents();
        BindOverlapEvents();
    }
}
#endif
