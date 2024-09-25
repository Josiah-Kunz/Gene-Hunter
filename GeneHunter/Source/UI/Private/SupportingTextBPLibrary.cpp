// Fill out your copyright notice in the Description page of Project Settings.


#include "SupportingTextBPLibrary.h"

FText USupportingTextBPLibrary::GetDevNoteForDisplay(const FSupportingText& SupportingText)
{
	return FSupportingText::DoReplacements(SupportingText.DevNote);
}

FText USupportingTextBPLibrary::GetSummaryForDisplay(const FSupportingText& SupportingText)
{
	return FSupportingText::DoReplacements(SupportingText.Summary);
}

FText USupportingTextBPLibrary::GetDescriptionForDisplay(const FSupportingText& SupportingText)
{
	return FSupportingText::DoReplacements(SupportingText.Description);
}

FText USupportingTextBPLibrary::GetFlavorTextForDisplay(const FSupportingText& SupportingText)
{
	return FSupportingText::DoReplacements(SupportingText.FlavorText);
}