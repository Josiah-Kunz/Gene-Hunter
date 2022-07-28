

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "EditorBackgroundParent.generated.h"

/**
 * A class to augment the EditorBackground class. Mostly used to give the dev access to the width of the "right menu".
 */
UCLASS()
class UI_API UEditorBackgroundParent : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Right Menu")
	UButton* ClickOffButton;
	
	/** Width of the "right menu". Also, (screen width - Width) is the width of the "click off" button (dim area). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Right Menu")
	float Width;
	
	//overrides
	virtual void SynchronizeProperties() override;

	virtual bool Initialize() override;
	
};
