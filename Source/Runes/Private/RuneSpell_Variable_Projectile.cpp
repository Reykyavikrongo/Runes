// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Variable_Projectile.h"

void URuneSpell_Variable_Projectile::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Variable Projectile casted"));
}
