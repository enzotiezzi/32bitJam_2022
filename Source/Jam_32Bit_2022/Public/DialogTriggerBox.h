// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Dialog.h>
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DialogTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class JAM_32BIT_2022_API ADialogTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UDialog> DialogRef;
};
