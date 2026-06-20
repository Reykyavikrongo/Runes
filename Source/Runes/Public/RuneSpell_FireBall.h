// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneSpell.h"
#include "RuneSpell_FireBall.generated.h"

class AFireBallProjectile;

/**
 * 
 */
UCLASS()
class RUNES_API URuneSpell_FireBall : public URuneSpell
{
	GENERATED_BODY()
	
public:
	virtual void Cast(const FSpellCastContext& Context) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFireBallProjectile> fireBall = nullptr;
};
