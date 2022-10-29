// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTriggerBox.h"
#include <Kismet/GameplayStatics.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>

void ADialogTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (DialogRef)
	{
		if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			SetActorEnableCollision(false);

			MyGameMode->DialogSystem->StartDialog(DialogRef.GetDefaultObject());
		}
	}
}