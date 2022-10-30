// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/SphereComponent.h>
#include <Attack.h>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class JAM_32BIT_2022_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Spring Arm Component to follow the camera behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArmComp;

	//Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;

	//Called for forwards/backward input
	void MoveForward(float InputAxis);

	//called for left/right side input
	void MoveRight(float InputAxis);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackCombo();

	bool ExecuteAttack(UAttack* uCurrentAttack);

	void RollAttack();

	UFUNCTION(BlueprintCallable)
		void ResetCombat();

	UFUNCTION(BlueprintCallable)
		void ContinueCombo();

	UFUNCTION()
		void Interact();

	UFUNCTION()
		void StopDialog();

	UFUNCTION()
		void StartDialog();

protected:
	/*
	*
	*
	*  ATTACK
	*
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		TArray<TSubclassOf<UAttack>> ComboAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		TSubclassOf<UAttack> LaserBeamAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		TSubclassOf<UAttack> RollingAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		float RollingSpeed = 600;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		float RollingRotationSpeed = 1;

	UPROPERTY(BlueprintReadWrite)
		float CurrentYawRotation = 0;

	UPROPERTY(BlueprintReadWrite)
		float InitialYawRotation = 0;

	UPROPERTY(BlueprintReadWrite)
		bool bIsRolling = false;

	UPROPERTY(BlueprintReadWrite)
		FTimerHandle RollAttackTimerHandle;

	void RollAttackTick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack System")
		TSubclassOf<UAttack> UltimateAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UAttack* CurrentAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bContinueCombo = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int ComboCounter = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsRootMotionAnimation = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bCanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack System")
		USphereComponent* RightHandCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack System")
		USphereComponent* LeftHandCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack System")
		USphereComponent* TailCollider;

	UFUNCTION(BlueprintCallable)
		void EnableRightHandCollider();

	UFUNCTION(BlueprintCallable)
		void EnableLeftHandCollider();

	UFUNCTION(BlueprintCallable)
		void EnableTailCollider();

	UFUNCTION()
		void OnHitComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AttackAudioComponent;

	/*
	*
	*
	* ENDURANCE SYSTEM
	*
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edurance System")
		float MaxEndurance = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Edurance System")
		float CurrentEndurance = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Edurance System")
		bool bCanRecoverEndurance;

	/*
	*
	* DIALOG SYSTEM
	* 
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialog System")
		bool bIsInDialog = false;
};
