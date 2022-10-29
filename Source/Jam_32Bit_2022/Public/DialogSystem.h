// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <LevelSequencePlayer.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <BaseUserWidget.h>
#include <Dialog.h>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JAM_32BIT_2022_API UDialogSystem : public UObject
{
	GENERATED_BODY()

public:
	UWorld* World;

	void SetupWidget();

	void StartDialog(UDialog* NewDialog);

	void PlayDialogItem(UDialogItem* DialogItem);

	void PlayNextDialog();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UDialog* CurrentDialog;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UDialogItem* CurrentDialogItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<UDialogItem>> DialogLines;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UBaseUserWidget> WidgetRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		UBaseUserWidget* Widget;

	UPROPERTY(BlueprintReadWrite)
		UImage* LeadingImage;

	UPROPERTY(BlueprintReadWrite)
		UImage* TrailingImage;

	UPROPERTY(BlueprintReadWrite) 
		UTextBlock* DialogText;

	UPROPERTY(BlueprintReadWrite)
		ULevelSequencePlayer* CurrentSequencePlayer;
};