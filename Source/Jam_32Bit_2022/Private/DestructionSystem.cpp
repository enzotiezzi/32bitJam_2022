// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionSystem.h"
#include <Kismet/GameplayStatics.h>
#include <Building.h>
#include <Statue.h>

void UDestructionSystem::Start()
{
	SetupWidget();

	TArray<AActor*> Buildings;

	UGameplayStatics::GetAllActorsOfClass(World, ABuilding::StaticClass(), Buildings);

	InitialBuildingCount = Buildings.Num();

	UpdateBuildingPercentage();
}

void UDestructionSystem::SetupWidget()
{
	if (WidgetRef)
	{
		Widget = Cast<UBaseUserWidget>(CreateWidget<UUserWidget>(World, WidgetRef));

		if (Widget)
		{
			TextPercentage = Cast<UTextBlock>(Widget->GetWidgetFromName("DestructionText"));
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
	TArray<AActor*> Buildings;

	UGameplayStatics::GetAllActorsOfClass(World, ABuilding::StaticClass(), Buildings);

	float Percentage = 100 - ((Buildings.Num() / InitialBuildingCount) * 100);

	TextPercentage->SetText(FText::FromString(FString::SanitizeFloat(Percentage) + "%"));

	if (Percentage >= 80)
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