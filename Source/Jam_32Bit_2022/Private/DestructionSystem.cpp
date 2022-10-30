// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionSystem.h"
#include <Kismet/GameplayStatics.h>
#include <Building.h>
#include <Statue.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>

void UDestructionSystem::Start()
{
	SetupWidget();

	AActor* LevelSettingsActor = UGameplayStatics::GetActorOfClass(World, ALevelSettings::StaticClass());

	if (LevelSettingsActor)
		LevelSettings = Cast<ALevelSettings>(LevelSettingsActor);

	TArray<AActor*> Buildings;

	UGameplayStatics::GetAllActorsOfClass(World, ABuilding::StaticClass(), Buildings);

	InitialBuildingCount = Buildings.Num();

	UpdateBuildingPercentage();

	CurrentTimer = LevelSettings->TimeToGameOver * 60;

	StartTimer();
}

void UDestructionSystem::SetupWidget()
{
	if (WidgetRef)
	{
		Widget = Cast<UBaseUserWidget>(CreateWidget<UUserWidget>(World, WidgetRef));

		if (Widget)
		{
			TextPercentage = Cast<UTextBlock>(Widget->GetWidgetFromName("DestructionText"));
			EnduranceBar = Cast<UProgressBar>(Widget->GetWidgetFromName("EnduranceBar"));
			Timer = Cast<UTextBlock>(Widget->GetWidgetFromName("Timer"));
		}
	}
}

void UDestructionSystem::ShowWidget()
{
	if (Widget)
	{
		if (!Widget->IsInViewport())
			Widget->AddToViewport();
	}
}

void UDestructionSystem::UpdateBuildingPercentage()
{
	if (LevelSettings)
	{
		TArray<AActor*> Buildings;

		UGameplayStatics::GetAllActorsOfClass(World, ABuilding::StaticClass(), Buildings);

		float Percentage = FMath::RoundToInt(100 - ((static_cast<float>(Buildings.Num()) / static_cast<float>(InitialBuildingCount)) * 100));

		TextPercentage->SetText(FText::FromString(FString::SanitizeFloat(Percentage) + "%"));

		if (Percentage >= LevelSettings->PercentageToActivateStatue)
		{
			TArray<AActor*> Statues;

			UGameplayStatics::GetAllActorsOfClass(World, AStatue::StaticClass(), Statues);

			for (AActor* StatueActor : Statues)
			{
				if (AStatue* Statue = Cast<AStatue>(StatueActor))
				{
					Statue->ActivateStatue();
				}
			}
		}
	}
}

void UDestructionSystem::UpdateEnduranceBar(float EndurancePercentage)
{
	EnduranceBar->SetPercent(EndurancePercentage);
}

void UDestructionSystem::StartTimer()
{
	World->GetTimerManager().ClearTimer(TimerHandle);

	World->GetTimerManager().SetTimer(TimerHandle, this, &UDestructionSystem::TimerTick, TimerDecrement, true);
}

void UDestructionSystem::TimerTick()
{
	if (CurrentTimer > 0)
	{
		CurrentTimer -= TimerDecrement;

		int Minutes = CurrentTimer / 60;
		int Seconds = CurrentTimer % 60;

		FString TimeLeft = FString::FromInt(Minutes) + ":" + FString::FromInt(Seconds);

		Timer->SetText(FText::FromString(TimeLeft));
	}
	else 
	{
		World->GetTimerManager().ClearTimer(TimerHandle);

		if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(World)))
		{
			MyGameMode->ShowGameOver();
		}
	}
}