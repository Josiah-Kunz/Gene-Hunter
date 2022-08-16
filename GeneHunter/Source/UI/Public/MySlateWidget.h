#pragma once
#include "Components/Widget.h"
#include "SMySlateWidget.h"

#include "MySlateWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEvent);

UCLASS()
class UI_API UMySlateWidget : public UWidget
{

	GENERATED_BODY()
	
public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

	/** Called when the background is clicked */
	UPROPERTY(BlueprintAssignable, Category="Event")
	FOnButtonClickedEvent OnClicked;
	

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<SMySlateWidget> MySlateWidget;
	
};
