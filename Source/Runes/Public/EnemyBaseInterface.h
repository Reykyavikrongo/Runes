// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class RUNES_API UEnemyBaseInterface : public UInterface
{
	GENERATED_BODY()
public:
	UEnemyBaseInterface();
	~UEnemyBaseInterface();
};

class IEnemyBaseInterface
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(float Amount) = 0;
};
