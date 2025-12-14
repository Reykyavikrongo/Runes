// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneInvokerComponent.h"
#include "RuneRing.h"
#include "RuneSpell.h"
#include "RuneSpellData.h"

void URuneInvokerComponent::Initialize(ARuneRing* InRuneRing)
{
	RuneRing = InRuneRing;
}

void URuneInvokerComponent::InvokeSpell()
{
	if (!RuneRing) return;

	const TArray<ERune>& Runes = RuneRing->GetRunes();

	//for (URuneSpellData* Data : AllSpells)
	//{
	//	if (!Data || Data->RunePattern != Runes) continue;
	//
	//	URuneSpell* NewSpell = NewObject<URuneSpell>(this, Data->SpellClass);
	//	NewSpell->SpellName = Data->SpellName;
	//	NewSpell->Icon = Data->Icon;
	//
	//	if (InvokedSpells.Num() >= 3)
	//	{
	//		InvokedSpells.RemoveAt(0);
	//	}
	//
	//	InvokedSpells.Add(NewSpell);
	//	return;
	//}
}

const TArray<URuneSpell*>& URuneInvokerComponent::GetInvokedSpells() const
{
	return InvokedSpells;
}

