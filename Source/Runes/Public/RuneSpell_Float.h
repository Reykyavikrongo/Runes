// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneSpell.h"
#include "RuneSpell_Float.generated.h"

/**
 * 
 */
UCLASS()
class RUNES_API URuneSpell_Float : public URuneSpell
{
	GENERATED_BODY()
	
public:
	virtual void Cast(const FSpellCastContext& Context) override;
};
