// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Components/Button.h>
#include <DestructionSystem.h>
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

	UPROPERTY(BlueprintReadWrite, Category = "Destruction System")
		UDestructionSystem* DestructionSystem;

	UPROPERTY(BlueprintReadWrite, Category = "Game Over")
		UUserWidget* GameOverWidget;

	UFUNCTION()
		void ShowGameOver();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog System")
		TSubclassOf<UDialogSystem> DialogSystemRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destruction System")
		TSubclassOf<UDestructionSystem> DestructionSystemRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Over")
		TSubclassOf<UUserWidget> GameOverWidgetRef;

	UPROPERTY(BlueprintReadWrite)
		UButton* GameOverMenuButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* GameOverRetryButton;


	UFUNCTION()
		void OnMenuButtonClick();

	UFUNCTION()
		void OnRetryButtonClick();

	void SetupGameOverWidget();
};
