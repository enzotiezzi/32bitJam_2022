// Copyright Epic Games, Inc. All Rights Reserved.


#include "Jam_32Bit_2022GameModeBase.h"
#include <Kismet/GameplayStatics.h>

void AJam_32Bit_2022GameModeBase::BeginPlay()
{
	SetupMainMenuWidget();

	if (GetWorld()->GetFName() == "MenuLevel")
	{
		ShowMainMenu();
	}
	else
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

		SetupGameOverWidget();
		SetupPauseMenuWidget();
		SetupWinWidget();
	}
}

void AJam_32Bit_2022GameModeBase::SetupGameOverWidget()
{
	if (GameOverWidgetRef)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetRef);

		if (GameOverWidget)
		{
			GameOverMenuButton = Cast<UButton>(GameOverWidget->GetWidgetFromName("MenuButton"));
			GameOverRetryButton = Cast<UButton>(GameOverWidget->GetWidgetFromName("RetryButton"));

			GameOverMenuButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnMenuButtonClick);
			GameOverRetryButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnRetryButtonClick);
		}
	}
}

void AJam_32Bit_2022GameModeBase::OnMenuButtonClick()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (MainMenuWidget->IsInViewport())
			MainMenuWidget->RemoveFromViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		PlayerController->SetShowMouseCursor(false);

		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
}

void AJam_32Bit_2022GameModeBase::OnRetryButtonClick()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		GameOverWidget->RemoveFromViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		PlayerController->SetShowMouseCursor(false);

		PlayerController->SetInputMode(FInputModeGameOnly());

		UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
	}
}

void AJam_32Bit_2022GameModeBase::ShowGameOver()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		GameOverWidget->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		PlayerController->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetWidgetToFocus(GameOverWidget->GetWidgetFromName("RetryButton")->TakeWidget());

		PlayerController->SetInputMode(InputMode);
	}
}

void AJam_32Bit_2022GameModeBase::SetupMainMenuWidget()
{
	if (MainMenuWidgetRef)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetRef);

		if (MainMenuWidget)
		{
			MainMenuStartButton = Cast<UButton>(MainMenuWidget->GetWidgetFromName("StartButton"));
			MainMenuQuitButton = Cast<UButton>(MainMenuWidget->GetWidgetFromName("QuitButton"));

			MainMenuStartButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnStartButtonClick);
			MainMenuQuitButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnQuitButtonClick);
		}
	}
}

void AJam_32Bit_2022GameModeBase::OnStartButtonClick()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (MainMenuWidget->IsInViewport())
			MainMenuWidget->RemoveFromViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		PlayerController->SetShowMouseCursor(false);

		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::OpenLevel(GetWorld(), "Level_1");
}

void AJam_32Bit_2022GameModeBase::OnQuitButtonClick()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
	}
}

void AJam_32Bit_2022GameModeBase::ShowMainMenu()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (!MainMenuWidget->IsInViewport())
			MainMenuWidget->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		PlayerController->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetWidgetToFocus(MainMenuStartButton->TakeWidget());

		PlayerController->SetInputMode(InputMode);
	}
}

void AJam_32Bit_2022GameModeBase::SetupPauseMenuWidget()
{
	if (PauseWidgetRef)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetRef);

		if (PauseMenuWidget)
		{
			PauseMenuResumeButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("ResumeButton"));
			PauseMenuRestartButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("RestartButton"));
			PauseMenuMainMenuButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("MenuButton"));
		
			PauseMenuResumeButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnResumeButtonClick);
			PauseMenuRestartButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnRetryButtonClick);
			PauseMenuMainMenuButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnMenuButtonClick);
		}
	}
}

void AJam_32Bit_2022GameModeBase::OnResumeButtonClick()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (PauseMenuWidget->IsInViewport())
		{
			PauseMenuWidget->RemoveFromViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), false);

			PlayerController->SetShowMouseCursor(false);

			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AJam_32Bit_2022GameModeBase::ShowPauseMenu()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (PauseMenuWidget)
		{
			if (!PauseMenuWidget->IsInViewport())
				PauseMenuWidget->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);

			PlayerController->SetShowMouseCursor(true);

			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			InputMode.SetWidgetToFocus(PauseMenuResumeButton->TakeWidget());

			PlayerController->SetInputMode(InputMode);
		}
	}
}

void AJam_32Bit_2022GameModeBase::SetupWinWidget()
{
	if (WinWidgetRef)
	{
		WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetRef);

		if (WinWidget)
		{
			TimeLeftText = Cast<UTextBlock>(WinWidget->GetWidgetFromName("TimeLeftText"));
			DestructionText = Cast<UTextBlock>(WinWidget->GetWidgetFromName("DestructionText"));
			WinMenuRetryButton = Cast<UButton>(WinWidget->GetWidgetFromName("RetryButton"));
			WinMenuNextButton = Cast<UButton>(WinWidget->GetWidgetFromName("NextButton"));

			WinMenuRetryButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::OnRetryButtonClick);
			WinMenuNextButton->OnClicked.AddDynamic(this, &AJam_32Bit_2022GameModeBase::GoToNextLevel);
		}
	}
}

void AJam_32Bit_2022GameModeBase::GoToNextLevel()
{
	if (!CurrentNextLevelName.IsNone())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			PlayerController->SetShowMouseCursor(false);

			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		UGameplayStatics::OpenLevel(GetWorld(), CurrentNextLevelName);
	}
}

void AJam_32Bit_2022GameModeBase::ShowWinWidget(FName NextLevelName)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		CurrentNextLevelName = NextLevelName;

		DestructionSystem->UpdateBuildingPercentage();

		// TODO: SET TIME LEFT AND 
		int Minutes = DestructionSystem->CurrentTimer / 60;
		int Seconds = DestructionSystem->CurrentTimer % 60;

		FString TimeLeft = FString::FromInt(Minutes) + ":" + FString::FromInt(Seconds);

		TimeLeftText->SetText(FText::FromString(TimeLeft));
		DestructionText->SetText(FText::FromString(FString::SanitizeFloat(DestructionSystem->CurrentDestructionPercentage) + "%"));

		if (!WinWidget->IsInViewport())
			WinWidget->AddToViewport();
		
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		PlayerController->SetShowMouseCursor(true);

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetWidgetToFocus(WinMenuNextButton->TakeWidget());

		PlayerController->SetInputMode(InputMode);
	}
}