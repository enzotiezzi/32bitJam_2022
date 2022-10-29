// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JAM_32BIT_2022_API UAttack : public UObject
{
	GENERATED_BODY()
	
public:
	UAttack();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bUseEndurance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bRecoverEndurance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCanRotate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MaxRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int EnduranceCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int EnduranceToRecover;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bIsRootMotion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USoundBase* AttackSound;
};
