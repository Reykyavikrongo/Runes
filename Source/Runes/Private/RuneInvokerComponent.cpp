// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneInvokerComponent.h"
#include "RuneRing.h"
#include "RuneSpell.h"
#include "RuneSpellData.h"

void URuneInvokerComponent::AddInvokedSpell(URuneSpell* RuneSpell)
{
    // Remove existing instance of the same spell (no duplicates)
    InvokedSpells.RemoveAll(
        [&](URuneSpell* Existing)
        {
            return Existing && Existing->GetClass() == RuneSpell->GetClass();
        }
    );

    // Insert newest spell at the front
    InvokedSpells.Insert(RuneSpell, 0);

    // Enforce max size (FIFO: remove oldest at the end)
    if (InvokedSpells.Num() > 3)
    {
        InvokedSpells.RemoveAt(InvokedSpells.Num() - 1);
    }
}

void URuneInvokerComponent::Initialize(ARuneRing* InRuneRing)
{
	RuneRing = InRuneRing;
}

void URuneInvokerComponent::InvokeSpell()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("entered the invoke function"));
    if (!RuneRing)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RuneRing doesn't exist"));
        return;
    }
    if (!SpellBook)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpellBook doesn't exist"));
        return;
    }
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("RuneRing and spellBook exist"));

    const TArray<ERune>& CurrentRunes = RuneRing->GetRunes();
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GotRunes succeded"));

    // Make a sorted copy of the current runes
    TArray<ERune> SortedCurrentRunes = CurrentRunes;
    SortedCurrentRunes.Sort();

    for (URuneSpellData* Data : SpellBook->Spells)
    {
        if (!Data) continue;

        // Make a sorted copy of the spell's rune pattern
        TArray<ERune> SortedPattern = Data->RunePattern;
        SortedPattern.Sort();

        if (SortedPattern == SortedCurrentRunes)
        {
            URuneSpell* Spell = NewObject<URuneSpell>(this, Data->SpellClass);

            Spell->SpellName = Data->SpellName;
            Spell->Icon = Data->Icon;
            Spell->RunePattern = Data->RunePattern;

            AddInvokedSpell(Spell);
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Added Invoked Spells"));
            return;
        }
    }
}

const TArray<URuneSpell*>& URuneInvokerComponent::GetInvokedSpells() const
{
	return InvokedSpells;
}

