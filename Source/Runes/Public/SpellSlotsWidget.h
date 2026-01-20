// Fill out your copyright notice in the Description page of Project Settings.

#pragma once 

#include "CoreMinimal.h" 
#include "Blueprint/UserWidget.h" 
#include "RuneSpell.h"
#include "SpellSlotsWidget.generated.h"

class URuneSpell;

UCLASS()
class RUNES_API USpellSlotsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSpellSlots(const TArray<URuneSpell*>& Spells);

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Slot1Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Slot2Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Slot3Text;

	void SetSlot(UTextBlock* SlotText, URuneSpell* Spell);
};

