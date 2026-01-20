// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellSlotsWidget.h"
#include "RuneSpell.h"
#include "Components/TextBlock.h"

void USpellSlotsWidget::UpdateSpellSlots(const TArray<URuneSpell*>& Spells)
{
	SetSlot(Slot1Text, Spells.IsValidIndex(0) ? Spells[0] : nullptr);
	SetSlot(Slot2Text, Spells.IsValidIndex(1) ? Spells[1] : nullptr);
	SetSlot(Slot3Text, Spells.IsValidIndex(2) ? Spells[2] : nullptr);
}

void USpellSlotsWidget::SetSlot(UTextBlock* SlotText, URuneSpell* Spell)
{
	if (!SlotText) return;

	if (Spell)
	{
		SlotText->SetText(FText::FromName(Spell->SpellName));
	}
	else
	{
		SlotText->SetText(FText::GetEmpty());
	}
}
