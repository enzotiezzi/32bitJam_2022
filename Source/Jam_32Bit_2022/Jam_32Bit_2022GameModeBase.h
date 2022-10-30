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

	void ShowPauseMenu();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog System")
		TSubclassOf<UDialogSystem> DialogSystemRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destruction System")
		TSubclassOf<UDestructionSystem> DestructionSystemRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Over")
		TSubclassOf<UUserWidget> GameOverWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Main Menu")
		TSubclassOf<UUserWidget> MainMenuWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pause Menu")
		TSubclassOf<UUserWidget> PauseWidgetRef;

	UPROPERTY(BlueprintReadWrite, Category = "Main Menu")
		UUserWidget* MainMenuWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Pause Menu")
		UUserWidget* PauseMenuWidget;

	UPROPERTY(BlueprintReadWrite)
		UButton* GameOverMenuButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* GameOverRetryButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* MainMenuStartButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* MainMenuQuitButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* PauseMenuResumeButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* PauseMenuRestartButton;

	UPROPERTY(BlueprintReadWrite)
		UButton* PauseMenuMainMenuButton;

	UFUNCTION()
		void OnMenuButtonClick();

	UFUNCTION()
		void OnRetryButtonClick();

	UFUNCTION()
		void OnStartButtonClick();

	UFUNCTION()
		void OnQuitButtonClick();

	UFUNCTION()
		void OnResumeButtonClick();

	void SetupGameOverWidget();

	void SetupMainMenuWidget();

	void SetupPauseMenuWidget();

	void ShowMainMenu();
};
