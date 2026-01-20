// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell.h"

URuneSpell::URuneSpell()
{
	CanBeCast = false;
}

void URuneSpell::Cast(const FSpellCastContext& Context)
{
	//base spell does nothing
}
