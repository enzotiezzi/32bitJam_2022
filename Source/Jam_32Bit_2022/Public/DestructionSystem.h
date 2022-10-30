// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <LevelSettings.h>
#include <Components/ProgressBar.h>
#include <BaseUserWidget.h>
#include <Components/TextBlock.h>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DestructionSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JAM_32BIT_2022_API UDestructionSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		UWorld* World;

	void Start();

	void ShowWidget();

	void UpdateBuildingPercentage();

	void UpdateEnduranceBar(float EndurancePercentage);

	void StartTimer();

	UPROPERTY(BlueprintReadWrite)
		int CurrentDestructionPercentage = 0;

	UPROPERTY(BlueprintReadWrite)
		int CurrentTimer;

protected:
	void SetupWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UBaseUserWidget> WidgetRef;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
		UBaseUserWidget* Widget;

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* TextPercentage;

	UPROPERTY(BlueprintReadWrite)
		UTextBlock* Timer;

	UPROPERTY(BlueprintReadWrite)
		UProgressBar* EnduranceBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int InitialBuildingCount;

	UPROPERTY(BlueprintReadWrite)
		ALevelSettings* LevelSettings;

	UPROPERTY(BlueprintReadWrite)
		FTimerHandle TimerHandle;

	void TimerTick();

	UPROPERTY(BlueprintReadWrite)
		int TimerDecrement = 1;
};
