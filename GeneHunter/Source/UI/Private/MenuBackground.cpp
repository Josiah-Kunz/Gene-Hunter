#include "MenuBackground.h"

void UMenuBackground::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UMenuBackground::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyCanvas.Reset();
}

TSharedRef<SWidget> UMenuBackground::RebuildWidget()
{
	
	Super::RebuildWidget();
	MyCanvas = SNew(SCanvas)
	
		+SCanvas::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			.Size(FVector2D{
				GetCachedGeometry().Size.X - MenuMargins.Left - MenuMargins.Right,
				GetCachedGeometry().Size.Y - MenuMargins.Top - MenuMargins.Bottom
			})
			[
					MyImage.ToSharedRef()
			]
	;

	return MyImage.ToSharedRef();
	
	//return MyCanvas.ToSharedRef();
}
