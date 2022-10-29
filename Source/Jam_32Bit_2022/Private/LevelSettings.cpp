// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSettings.h"
#include <Kismet/GameplayStatics.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>

void ALevelSettings::BeginPlay()
{
	Super::BeginPlay();

	if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->DestructionSystem->StartTimer();
	}
}