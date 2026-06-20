// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Turret.h"

void URuneSpell_Turret::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Turret casted"));
}
