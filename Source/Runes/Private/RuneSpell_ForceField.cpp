// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_ForceField.h"

void URuneSpell_ForceField::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ForceField casted"));
}
