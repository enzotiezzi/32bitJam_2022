// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <DialogSystem.h>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Jam_32Bit_2022GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class JAM_32BIT_2022_API AJam_32Bit_2022GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Dialog System")
		UDialogSystem* DialogSystem;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog System")
		TSubclassOf<UDialogSystem> DialogSystemRef;
};
