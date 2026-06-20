// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Float.h"

void URuneSpell_Float::Cast(const FSpellCastContext& Context)
{
    //nothing yet
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Float casted"));
}
