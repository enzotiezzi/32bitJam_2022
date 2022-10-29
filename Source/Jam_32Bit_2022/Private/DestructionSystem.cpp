// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionSystem.h"
#include <Kismet/GameplayStatics.h>
#include <Building.h>

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
	if (!Widget->IsInViewport())
		Widget->AddToViewport();
}

void UDestructionSystem::UpdateBuildingPercentage()
{
	TArray<AActor*> Buildings;

	UGameplayStatics::GetAllActorsOfClass(World, ABuilding::StaticClass(), Buildings);

	float Percentage = (Buildings.Num() / InitialBuildingCount) * 100;

	TextPercentage->SetText(FText::FromString(FString::SanitizeFloat(Percentage) + "%"));
}