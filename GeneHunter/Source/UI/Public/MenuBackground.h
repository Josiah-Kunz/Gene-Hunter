// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorStyleSet.h"
#include "Components/Image.h"
#include "Components/Widget.h"
#include "Widgets/SCanvas.h"

#include "MenuBackground.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBGClickedEvent);

/**
 * 
 */
UCLASS()
class UI_API UMenuBackground : public UImage
{
	GENERATED_BODY()
	//GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category=Settings)
	FMargin MenuMargins = {0, 0, 480, 0};


public:
	
	/**
	 * Called whenever the background is clicked.
	 */
	UPROPERTY(EditAnywhere, Category="Widget Event", meta=(DisplayName="OnBGClicked (MenuBackground)"))
	FOnBGClickedEvent OnBGClicked;
	
public:
	
	virtual void SynchronizeProperties() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	TSharedPtr<SCanvas> MyCanvas;

	
	
};
