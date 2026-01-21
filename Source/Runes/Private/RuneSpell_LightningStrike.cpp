// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_LightningStrike.h"
#include "RunesCharacter.h"
#include "Engine/World.h"

void URuneSpell_LightningStrike::Cast(const FSpellCastContext& Context)
{
    //nothing yet
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LightningStrike casted"));
}