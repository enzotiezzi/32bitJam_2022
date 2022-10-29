// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Explosion = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Explosion"));

	SetRootComponent(BoxComponent);

	StaticMeshComponent->SetupAttachment(BoxComponent);
	Explosion->SetupAttachment(BoxComponent);

	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	Explosion->SetVisibility(false);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABuilding::ReceiveDamange(float IncomingDamange) 
{
	if (IncomingDamange > 0 && CurrentHealth > 0) 
	{
		CurrentHealth -= IncomingDamange;

		if (CurrentHealth <= 0)
		{
			CurrentHealth = 0;

			StaticMeshComponent->SetVisibility(false);
			Explosion->SetVisibility(true);

			FTimerHandle DestroyTimer;
			GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [this]()
				{
					Destroy();
				}, TimeToDestroy, false);

			if (DestructionHitSound)
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DestructionHitSound, GetActorLocation());

			if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				MyGameMode->DestructionSystem->UpdateBuildingPercentage();
			}
		}
		else 
		{
			if (BasicHitSound)
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BasicHitSound, GetActorLocation());
		}
	}

	return CurrentHealth;
}