// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Building.h>
#include <Components/BoxComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Statue.generated.h"

UCLASS(Blueprintable)
class JAM_32BIT_2022_API AStatue : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float ReceiveDamange(float IncomingDamage) override;

	void ActivateStatue();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Barrier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundBase* BarrierHitSound;

	UPROPERTY(BlueprintReadWrite)
		bool bIsBarrierUp = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Next Level")
		FName NextLevelName;
};
