#pragma once
#include "AffinitiesComponent.h"
#include "AffinitiesUnitTestUtilities.generated.h"

UCLASS()
class UAffinitiesUnitTestUtilities : public UBlueprintFunctionLibrary
{
public:

	GENERATED_BODY()
	
	constexpr static float TOLERANCE = 0.1F;

#define DUMMY_AFFINITIESCOMPONENT \
	UWorld* DummyWorld = UWorld::CreateWorld(EWorldType::Game, false); \
	AActor* DummyActor = DummyWorld->SpawnActor(AActor::StaticClass()); \
	UAffinitiesComponent* AffinitiesComponent = NewObject<UAffinitiesComponent>(DummyActor); \
	AffinitiesComponent->RegisterComponent(); 

#define DUMMY_GC \
	DummyWorld->DestroyWorld(false);
	
};