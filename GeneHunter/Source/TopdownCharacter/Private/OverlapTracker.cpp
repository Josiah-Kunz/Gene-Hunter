#include "OverlapTracker.h"

#include "Components/ShapeComponent.h"
#include "GameFramework/Actor.h"

UOverlapTracker::UOverlapTracker()
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

void UOverlapTracker::SetCollisionComponent(UShapeComponent* NewCollider)
{
    CollisionComponent = NewCollider;
    BindOverlapEvents();
}

void UOverlapTracker::SetCollisionLocation(const FVector WorldLocation)
{
    CollisionComponent->SetWorldLocation(WorldLocation);
}

void UOverlapTracker::BeginPlay()
{
    Super::BeginPlay();

    // Bind the collider's events
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
        //CollisionComponent->InitializeComponent();

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
                                     UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex,
                                     const bool bFromSweep, const FHitResult& SweepResult)
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

        // Fire events
        BeginOverlap.Broadcast(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
        
    }
}

void UOverlapTracker::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                   UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {

        // Remove components
        for (UActorComponent* Component : OtherActor->GetComponents())
        {
            UClass* ComponentClass = Component->GetClass();
            if (TrackedComponents.Contains(ComponentClass))
            {
                TArray<UActorComponent*>* Components = TrackedComponentInstances.Find(ComponentClass);
                if (Components && Components->Contains(Component))
                {
                    Components->Remove(Component);
                }
            }
        }

        // Remove actor
        OverlappingActors.Remove(OtherActor);
    }

    // Fire events
    EndOverlap.Broadcast(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}
