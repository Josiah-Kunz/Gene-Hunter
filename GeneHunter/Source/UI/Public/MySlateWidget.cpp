#include "MySlateWidget.h"

void UMySlateWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MySlateWidget.Reset();
}

TSharedRef<SWidget> UMySlateWidget::RebuildWidget()
{
	MySlateWidget = SNew(SMySlateWidget)
		.Brush(&Brush)
	;
	return MySlateWidget.ToSharedRef();
}

