// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "IndependentComponent.h"
#include "Components/ActorComponent.h"
#include "DependentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDependentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDependentComponent();

	virtual void OnRegister() override;

	UPROPERTY(EditAnywhere, Category="I Need This!")
	UCombatStatsComponent* Stats;

	UPROPERTY(EditAnywhere, Category="I Need This!")
	UIndependentComponent* Indy;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	float MsgTime;
	float MsgGap = 1;
	
};
