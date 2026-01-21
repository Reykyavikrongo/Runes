// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneSpell.h"
#include "RuneSpell_LightningStrike.generated.h"

/**
 * 
 */
UCLASS()
class RUNES_API URuneSpell_LightningStrike : public URuneSpell
{
	GENERATED_BODY()

public:
    virtual void Cast(const FSpellCastContext& Context) override;

protected:
    UPROPERTY()
    AActor* LightningStrike = nullptr;
};
