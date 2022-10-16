// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class UBaseWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UBaseWidgetComponent();

	UWidgetAnimation* GetAnimation(FText AnimationName);
};
