#pragma once
#include "Components/Widget.h"
#include "SMySlateWidget.h"

#include "MySlateWidget.generated.h"

UCLASS()
class UI_API UMySlateWidget : public UWidget
{

	GENERATED_BODY()
	
public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<SMySlateWidget> MySlateWidget;
	
};
