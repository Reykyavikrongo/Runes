// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Hook.h"

void URuneSpell_Hook::Cast(const FSpellCastContext& Context)
{
	//nothing yet
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hook casted"));
}
