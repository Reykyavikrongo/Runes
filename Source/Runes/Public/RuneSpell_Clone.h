// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneSpell.h"
#include "RuneSpell_Clone.generated.h"

class ACloneActor;

/**
 * 
 */
UCLASS()
class RUNES_API URuneSpell_Clone : public URuneSpell
{
	GENERATED_BODY()

public:
    virtual void Cast(const FSpellCastContext& Context) override;

protected:
    UPROPERTY()
    TObjectPtr<ACloneActor> ActiveClone = nullptr;
};
