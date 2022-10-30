// Fill out your copyright notice in the Description page of Project Settings.


#include "Statue.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AStatue::AStatue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Barrier = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrier"));

	Barrier->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AStatue::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStatue::ActivateStatue()
{
	bIsBarrierUp = false;

	Barrier->DestroyComponent();
}

float AStatue::ReceiveDamange(float IncomingDamage)
{
	if (bIsBarrierUp)
	{
		if (BarrierHitSound)
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BarrierHitSound, Barrier->GetComponentLocation());

		return 0;
	}
	else 
	{
		return Super::ReceiveDamange(IncomingDamage);
	}
}

void AStatue::GoToNextLevel()
{
	if (!NextLevelName.IsNone())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			PlayerController->SetShowMouseCursor(false);

			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
}