// Fill out your copyright notice in the Description page of Project Settings.


#include "Statue.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>

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
	if (Barrier)
	{
		bIsBarrierUp = false;

		Barrier->DestroyComponent();
	}
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
		CurrentHealth = Super::ReceiveDamange(IncomingDamage);

		if (CurrentHealth == 0)
		{
			if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);

				Destroy();

				MyGameMode->ShowWinWidget(NextLevelName);
			}
		}

		return CurrentHealth;
	}
}


