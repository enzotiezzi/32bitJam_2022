// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Destructible.h>
#include <Building.h>
#include <Jam_32Bit_2022/Jam_32Bit_2022GameModeBase.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	RightHandCollider = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollider"));
	LeftHandCollider = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollider"));
	TailCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TailCollider"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, 90.0f, 0.0f)));

	SpringArmComp->SetupAttachment(GetMesh());

	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	RightHandCollider->SetupAttachment(GetMesh(), "claw_rightSocket");
	LeftHandCollider->SetupAttachment(GetMesh(), "claw_leftSocket");
	TailCollider->SetupAttachment(GetMesh(), "tail4Socket");
	StaticMeshComponent->SetupAttachment(GetMesh(), "MouthSocket");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bIgnoreBaseRotation = false;

	RightHandCollider->SetCollisionProfileName("OverlapAllDynamic");
	LeftHandCollider->SetCollisionProfileName("OverlapAllDynamic");
	TailCollider->SetCollisionProfileName("OverlapAllDynamic");

	RightHandCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnHitComponentBeginOverlap);
	LeftHandCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnHitComponentBeginOverlap);
	TailCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnHitComponentBeginOverlap);

	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TailCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnHitComponentBeginOverlap);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("ComboAttack", IE_Pressed, this, &APlayerCharacter::AttackCombo);
	PlayerInputComponent->BindAction("RollAttack", IE_Pressed, this, &APlayerCharacter::RollAttack);
	PlayerInputComponent->BindAction("BeamAttack", IE_Pressed, this, &APlayerCharacter::BeamAttack);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &APlayerCharacter::UseUltimateAttack);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("PauseGame", IE_Pressed, this, &APlayerCharacter::PauseGame);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!bIsRolling)
	{
		if ((Controller != nullptr) && (AxisValue != 0.0f) && bCanMove)
		{
			// Find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// Get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, AxisValue);
		}
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (bIsRolling)
	{
		CurrentYawRotation += AxisValue * RollingRotationSpeed;

		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw = FMath::Clamp(InitialYawRotation + CurrentYawRotation, InitialYawRotation - CurrentAttack->MaxRotation, InitialYawRotation + CurrentAttack->MaxRotation);

		SetActorRotation(CurrentRotation);
	}
	else
	{
		if ((Controller != nullptr) && (AxisValue != 0.0f) && bCanMove)
		{
			// Find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// Get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// Add movement in that direction
			AddMovementInput(Direction, AxisValue);
		}
	}
}

void APlayerCharacter::AttackCombo()
{
	if (bCanMove)
	{
		if (!bIsAttacking)
			ExecuteAttack(ComboAttack[0].GetDefaultObject());
		else
			bContinueCombo = true;
	}
}

bool APlayerCharacter::ExecuteAttack(UAttack* uCurrentAttack)
{
	if (uCurrentAttack)
	{
		bool CanAttack = true;

		if (uCurrentAttack->bUseEndurance)
		{
			if (CurrentEndurance - uCurrentAttack->EnduranceCost >= 0)
			{
				if (!uCurrentAttack->bUseEnduranceOverTime)
					CurrentEndurance -= uCurrentAttack->EnduranceCost;

				if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
				{
					MyGameMode->DestructionSystem->UpdateEnduranceBar(CurrentEndurance / MaxEndurance);
				}
			}
			else
				CanAttack = false;
		}

		if (CanAttack)
		{
			CurrentAttack = uCurrentAttack;

			ComboCounter++;

			bIsAttacking = true;

			bIsRootMotionAnimation = CurrentAttack->bIsRootMotion;

			GetCharacterMovement()->AddImpulse(GetActorForwardVector() * uCurrentAttack->Impulse, true);

			PlayAnimMontage(CurrentAttack->AttackAnimMontage);

			if (uCurrentAttack->AttackSound)
				AttackAudioComponent = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), uCurrentAttack->AttackSound, GetActorLocation());
		}

		return CanAttack;
	}

	return false;
}

void APlayerCharacter::ContinueCombo()
{
	if (bContinueCombo)
	{
		bContinueCombo = false;

		ExecuteAttack(ComboAttack[ComboCounter].GetDefaultObject());
	}
}

void APlayerCharacter::RollAttack()
{
	if (!bIsRolling)
	{
		CurrentYawRotation = 0;
		InitialYawRotation = GetActorRotation().Yaw;

		bool CanAttack = ExecuteAttack(RollingAttack.GetDefaultObject());

		if (CanAttack)
		{
			bIsRolling = true;

			GetWorld()->GetTimerManager().SetTimer(RollAttackTimerHandle, this, &APlayerCharacter::RollAttackTick, GetWorld()->GetDeltaSeconds(), true);
			GetWorld()->GetTimerManager().SetTimer(EnduranceTimerHandle, this, &APlayerCharacter::DecreaseEnduranceTick, .1, true);
		}
	}
	else
	{
		if (RollAttackTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(RollAttackTimerHandle);

		if (EnduranceTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(EnduranceTimerHandle);

		ResetCombat();
	}
}



void APlayerCharacter::ExecuteUltimate()
{
	TArray<FHitResult> OutHits;

	// start and end locations
	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation();

	// create a collision sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(CurrentAttack->AttackRadius);


	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		// loop through TArray
		for (auto& Hit : OutHits)
		{
			if (ABuilding* Building = Cast<ABuilding>(Hit.GetActor()))
			{


				if (CurrentAttack)
				{

					if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
					{
						MyGameMode->DestructionSystem->UpdateEnduranceBar(CurrentEndurance / MaxEndurance);
					}

					Building->ReceiveDamange(CurrentAttack->Damage);
				}
			}
			
		}
	}



}


void APlayerCharacter::UseUltimateAttack()
{
	bool CanAttack = ExecuteAttack(UltimateAttack.GetDefaultObject());

	if (CanAttack)
	{
		bCanMove = false;
	}
}


void APlayerCharacter::BeamAttack()
{
	if (RollAttackTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(RollAttackTimerHandle);

	if (!bIsAttacking)
	{
		CurrentYawRotation = 0;
		InitialYawRotation = GetActorRotation().Yaw;

		bool CanAttack = ExecuteAttack(LaserBeamAttack.GetDefaultObject());

		if (CanAttack)
		{
			bIsRolling = true;
		}
	}
	else
	{
		if (EnduranceTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(EnduranceTimerHandle);

		ResetCombat();
	}
}

void APlayerCharacter::RollAttackTick()
{
	GetCharacterMovement()->AddImpulse(GetActorForwardVector() * RollingSpeed, true);
}

void APlayerCharacter::ResetCombat()
{
	ComboCounter = 0;

	CurrentYawRotation = 0;

	bIsAttacking = false;

	bIsRolling = false;

	bCanMove = true;

	bContinueCombo = false;

	bIsRootMotionAnimation = false;

	if (CurrentAttack)
		StopAnimMontage(CurrentAttack->AttackAnimMontage);

	CurrentAttack = nullptr;

	if (AttackAudioComponent)
		AttackAudioComponent->Stop();

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetVisibility(false);
}

void APlayerCharacter::EnableRightHandCollider()
{
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APlayerCharacter::EnableLeftHandCollider()
{
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APlayerCharacter::EnableTailCollider()
{
	TailCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APlayerCharacter::OnHitComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABuilding* Building = Cast<ABuilding>(OtherActor))
	{
		RightHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TailCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (CurrentAttack)
		{
			if (CurrentAttack->bRecoverEndurance)
			{
				CurrentEndurance += Building->EnduranceToRecover;

				CurrentEndurance = FMath::Clamp(CurrentEndurance, 0, MaxEndurance);

				if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
				{
					MyGameMode->DestructionSystem->UpdateEnduranceBar(CurrentEndurance / MaxEndurance);
				}
			}
			Building->ReceiveDamange(CurrentAttack->Damage);
		}
	}
}

void APlayerCharacter::StopDialog()
{
	bIsInDialog = false;
	bCanMove = true;
}

void APlayerCharacter::StartDialog()
{
	bIsInDialog = true;
	bCanMove = false;
}

void APlayerCharacter::Interact()
{
	if (bIsInDialog)
	{
		if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			MyGameMode->DialogSystem->PlayNextDialog();
		}
	}
}

void APlayerCharacter::PauseGame()
{
	if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->ShowPauseMenu();
	}
}

void APlayerCharacter::EnableBeam()
{
	GetWorld()->GetTimerManager().SetTimer(EnduranceTimerHandle, this, &APlayerCharacter::DecreaseEnduranceTick, .1, true);

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMeshComponent->SetVisibility(true);
}

void APlayerCharacter::DecreaseEnduranceTick()
{
	if (CurrentAttack)
	{
		if (CurrentEndurance - CurrentAttack->EnduranceCost >= 0)
		{
			CurrentEndurance -= CurrentAttack->EnduranceCost;

			if (AJam_32Bit_2022GameModeBase* MyGameMode = Cast<AJam_32Bit_2022GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				MyGameMode->DestructionSystem->UpdateEnduranceBar(CurrentEndurance / MaxEndurance);
			}
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(EnduranceTimerHandle);
			GetWorld()->GetTimerManager().ClearTimer(RollAttackTimerHandle);

			ResetCombat();
		}
	}
}