// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JAM_32BIT_2022_API UDialogItem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TextLine")
		FString TextLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sequence")
		class ULevelSequence* Sequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sequence")
		bool HidePlayerOnSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thumbnail")
		UTexture2D* LeadingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thumbnail")
		UTexture2D* TrailingImage;
};


DECLARE_DELEGATE_OneParam(FOnDialogFinish, UDialogItem*);