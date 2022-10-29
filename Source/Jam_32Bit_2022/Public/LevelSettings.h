// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSettings.generated.h"

/**
 * 
 */
UCLASS()
class JAM_32BIT_2022_API ALevelSettings : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int TimeToGameOver;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int PercentageToActivateStatue;

protected:
	virtual void BeginPlay() override;
};
