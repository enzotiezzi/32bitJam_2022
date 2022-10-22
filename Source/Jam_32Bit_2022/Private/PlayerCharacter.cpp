// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

    SpringArmComp->SetupAttachment(GetMesh());

    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

    GetCharacterMovement()->bOrientRotationToMovement = false;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;

    GetCharacterMovement()->bIgnoreBaseRotation = false;
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
}

void APlayerCharacter::MoveForward(float AxisValue)
{
    if ((Controller != nullptr) && (AxisValue != 0.0f))
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

void APlayerCharacter::MoveRight(float AxisValue)
{
    if ((Controller != nullptr) && (AxisValue != 0.0f))
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

void APlayerCharacter::AttackCombo()
{
    if (!bIsAttacking)
        ExecuteAttack(ComboAttack[0].GetDefaultObject());
    else
        bContinueCombo = true;
}

void APlayerCharacter::ExecuteAttack(UAttack* uCurrentAttack)
{
    if (uCurrentAttack)
    {
        if (uCurrentAttack->bUseEndurance && uCurrentAttack->EnduranceCost - CurrentEndurance >= 0)
            CurrentEndurance -= uCurrentAttack->EnduranceCost;
        else
            return;

        if (uCurrentAttack->bRecoverEndurance)
        {
            CurrentEndurance += uCurrentAttack->EnduranceToRecover;

            CurrentEndurance = FMath::Clamp(CurrentEndurance, 0, MaxEndurance);
        }

        CurrentAttack = uCurrentAttack;

        ComboCounter++;

        bIsAttacking = true;

        bIsRootMotionAnimation = CurrentAttack->bIsRootMotion;

        PlayAnimMontage(CurrentAttack->AttackAnimMontage);
    }
}

void APlayerCharacter::ContinueCombo()
{
    if (bContinueCombo)
    {
        bContinueCombo = false;

        ExecuteAttack(ComboAttack[ComboCounter].GetDefaultObject());
    }
}

void APlayerCharacter::ResetCombat()
{
    ComboCounter = 0;

    bIsAttacking = false;

    bCanMove = true;

    bContinueCombo = false;

    bIsRootMotionAnimation = false;

    CurrentAttack = nullptr;
}