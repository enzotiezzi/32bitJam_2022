// Copyright Epic Games, Inc. All Rights Reserved.


#include "Jam_32Bit_2022GameModeBase.h"

void AJam_32Bit_2022GameModeBase::BeginPlay()
{
	if (DialogSystemRef)
	{
		DialogSystem = DialogSystemRef.GetDefaultObject();
		DialogSystem->World = GetWorld();
		DialogSystem->SetupWidget();
	}

	if (DestructionSystemRef)
	{
		DestructionSystem = DestructionSystemRef.GetDefaultObject();
		DestructionSystem->World = GetWorld();
		DestructionSystem->Start();
		DestructionSystem->ShowWidget();
	}
}