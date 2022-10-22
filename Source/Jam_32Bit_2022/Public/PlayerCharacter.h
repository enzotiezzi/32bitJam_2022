// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	void ExecuteAttack(UAttack* uCurrentAttack);

	UFUNCTION(BlueprintCallable)
	void ResetCombat();

	UFUNCTION(BlueprintCallable)
	void ContinueCombo();

protected:
	/*
	*
	* 
	*  ATTACK
	* 
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TArray<TSubclassOf<UAttack>> ComboAttack;

	UAttack* CurrentAttack;

	bool bContinueCombo = false;

	bool bIsAttacking = false;

	int ComboCounter = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsRootMotionAnimation = false;

	bool bCanMove = true;
};
