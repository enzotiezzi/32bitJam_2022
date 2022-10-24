// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Destructible.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UDestructible : public UInterface
{
	GENERATED_BODY()
};

class IDestructible 
{
	GENERATED_BODY()

public:
	virtual float ReceiveDamange(float IncomingDamage);
};