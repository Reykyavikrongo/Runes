// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Tornado.h"
#include "RunesCharacter.h"
#include "Engine/World.h"

void URuneSpell_Tornado::Cast(const FSpellCastContext& Context)
{
    //nothing yet
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Tornado casted"));
}