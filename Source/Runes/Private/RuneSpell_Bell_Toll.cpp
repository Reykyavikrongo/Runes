// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Bell_Toll.h"

void URuneSpell_Bell_Toll::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Bell Toll casted"));
}
