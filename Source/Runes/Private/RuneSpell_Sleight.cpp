// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Sleight.h"

void URuneSpell_Sleight::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Sleight casted"));
}
