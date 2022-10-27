// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <DialogItem.h>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dialog.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JAM_32BIT_2022_API UDialog : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogSystem")
		TArray<TSubclassOf<class UDialogItem>> Dialogs;

	FOnDialogFinish OnDialogFinish;

	UFUNCTION()
		virtual void OnDialogFinished(class UDialogItem* DialogItem);
};
