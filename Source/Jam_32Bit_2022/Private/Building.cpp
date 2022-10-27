// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include <Components/BoxComponent.h>

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(BoxComponent);

	StaticMeshComponent->SetupAttachment(BoxComponent);

	BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABuilding::ReceiveDamange(float IncomingDamange) 
{
	return 0;
}