// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JAM_32BIT_2022_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidgetAnimation* GetAnimation(FText AnimationName);
};
