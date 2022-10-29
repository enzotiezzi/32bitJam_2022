// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <PaperFlipbookComponent.h>
#include <Components/BoxComponent.h>
#include <Destructible.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS(Blueprintable)
class JAM_32BIT_2022_API ABuilding : public AActor, public IDestructible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float ReceiveDamange(float IncomingDamage) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnduranceToRecover;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundBase* BasicHitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundBase* DestructionHitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UPaperFlipbookComponent* Explosion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeToDestroy = 1;
};
