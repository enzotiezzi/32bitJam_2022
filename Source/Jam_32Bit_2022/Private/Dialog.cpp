// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog.h"
#include <Kismet/GameplayStatics.h>
#include <PlayerCharacter.h>

void UDialog::OnDialogFinished(class UDialogItem* DialogItem) 
{
	if (OnDialogFinish.IsBound())
		OnDialogFinish.Execute(DialogItem);

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(DialogItem->World, 0)->GetPawn()))
	{
		PlayerCharacter->StopDialog();
	}
}