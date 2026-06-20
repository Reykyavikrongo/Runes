// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Vortex.h"

void URuneSpell_Vortex::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Vortex casted"));
}
