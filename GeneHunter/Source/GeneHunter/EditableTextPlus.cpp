
#include "EditableTextPlus.h"
#include "Widgets/Input/SEditableText.h"
#include "Components/EditableText.h"

/*
 * Copied almost directly from EditableText.h, except that OnTextChanged now binds to HandleOnTextChangedOverride.
 * I wish I could dynamically copy the Super function, but I'm afraid I'm too unfamiliar with slate widgets and their
 * macros.
 */
TSharedRef<SWidget> UEditableTextPlus::RebuildWidget()
{
	MyEditableText = SNew( SEditableText )
		.Style( &WidgetStyle )
		.MinDesiredWidth( MinimumDesiredWidth )
		.IsCaretMovedWhenGainFocus( IsCaretMovedWhenGainFocus )
		.SelectAllTextWhenFocused( SelectAllTextWhenFocused )
		.RevertTextOnEscape( RevertTextOnEscape )
		.ClearKeyboardFocusOnCommit( ClearKeyboardFocusOnCommit )
		.SelectAllTextOnCommit( SelectAllTextOnCommit )
		.OnTextChanged( BIND_UOBJECT_DELEGATE( FOnTextChanged, HandleOnTextChangedOverride ) ) // This is the only line that's changed from EditableText.h
		.OnTextCommitted( BIND_UOBJECT_DELEGATE( FOnTextCommitted, HandleOnTextCommitted ) )
		.VirtualKeyboardType( EVirtualKeyboardType::AsKeyboardType( KeyboardType.GetValue() ) )
		.VirtualKeyboardOptions(VirtualKeyboardOptions)
		.VirtualKeyboardTrigger(VirtualKeyboardTrigger)
		.VirtualKeyboardDismissAction(VirtualKeyboardDismissAction)
		.Justification( Justification )
	;
	return MyEditableText.ToSharedRef();
}

void UEditableTextPlus::HandleOnTextChangedOverride(const FText& InText)
{
	HandleOnTextChanged(InText);
	if (!bChangedProgrammatic)
		OnChangedByUser.Broadcast(InText);
	else
		OnChangedByCode.Broadcast(InText);
	bChangedProgrammatic = false;
}

void UEditableTextPlus::SetTextProgrammatic(const FText& NewText)
{
	bChangedProgrammatic = true;
	SetText(NewText);
}

void UEditableTextPlus::SetFontColor(const FLinearColor& Color)
{
	WidgetStyle.SetColorAndOpacity(Color);
}

/** Aliases and almost useless functions. */
/** ===================================== */

void UEditableTextPlus::SetTextByCode(const FText& NewText)
{
	SetTextProgrammatic(NewText);
}

void UEditableTextPlus::SetTextByUser(const FText& NewText)
{
	SetText(NewText);
}

void UEditableTextPlus::SetTextInteractive(const FText& NewText)
{
	SetTextByUser(NewText);
}


