// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogSystem.h"

#include <BaseUserWidget.h>
#include <PlayerCharacter.h>
#include <Kismet/GameplayStatics.h>

void UDialogSystem::StartDialog(UDialog* NewDialog)
{
	CurrentDialog = NewDialog;
	DialogLines = NewDialog->Dialogs;

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(World, 0)->GetPawn()))
	{
		PlayerCharacter->StartDialog();
	}

	if (DialogLines.Num() > 0)
	{
		UDialogItem* DialogItem = DialogLines[0].GetDefaultObject();
		DialogItem->World = World;

		CurrentDialogItem = DialogItem;

		DialogLines.RemoveAt(0);

		PlayDialogItem(DialogItem);
	}
}

void UDialogSystem::PlayDialogItem(UDialogItem* DialogItem)
{
	if (!Widget->IsInViewport())
		Widget->AddToViewport();

	LeadingImage->Brush.SetResourceObject(DialogItem->LeadingImage);
	TrailingImage->Brush.SetResourceObject(DialogItem->TrailingImage);
	DialogText->SetText(FText::FromString(DialogItem->TextLine));

	if (CurrentSequencePlayer)
		CurrentSequencePlayer->Stop();

	if (DialogItem->Sequence)
	{
		ALevelSequenceActor* LevelSequenceActor;

		FMovieSceneSequencePlaybackSettings MovieSceneSequencePlaybackSettings;
		MovieSceneSequencePlaybackSettings.bPauseAtEnd = true;
		MovieSceneSequencePlaybackSettings.bHideHud = true;
		MovieSceneSequencePlaybackSettings.bHidePlayer = DialogItem->HidePlayerOnSequence;

		CurrentSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(World, DialogItem->Sequence, MovieSceneSequencePlaybackSettings, LevelSequenceActor);
	
		if (CurrentSequencePlayer)
			CurrentSequencePlayer->Play();
	}
}

void UDialogSystem::SetupWidget()
{
	if (WidgetRef)
	{
		Widget = CreateWidget<UBaseUserWidget>(World, WidgetRef);

		if (Widget)
		{
			LeadingImage = Cast<UImage>(Widget->GetWidgetFromName("Leading_Image"));
			TrailingImage = Cast<UImage>(Widget->GetWidgetFromName("Trailing_Image"));
			DialogText = Cast<UTextBlock>(Widget->GetWidgetFromName("DialogText"));
		}
	}
}

void UDialogSystem::PlayNextDialog()
{
	if (DialogLines.Num() > 0)
	{
		UDialogItem* DialogItem = DialogLines[0].GetDefaultObject();
		DialogLines.RemoveAt(0);

		PlayDialogItem(DialogItem);
	}
	else
	{
		if (Widget->IsInViewport())
			Widget->RemoveFromViewport();

		if (CurrentSequencePlayer)
			CurrentSequencePlayer->Stop();

		CurrentDialog->OnDialogFinished(CurrentDialogItem);
	}
}