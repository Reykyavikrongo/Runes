// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RuneRing.h"
#include "RuneSpell.generated.h"

class ARunesCharacter;

USTRUCT(BlueprintType)
struct FSpellCastContext
{
	GENERATED_BODY()

	UPROPERTY()
	ARunesCharacter* Caster = nullptr;

	UPROPERTY()
	AActor* Target = nullptr;

	UPROPERTY()
	FVector CastDirection = FVector::ZeroVector;

	UPROPERTY()
	ERune VariantRune; // optional
};


/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class RUNES_API URuneSpell : public UObject
{
	GENERATED_BODY()

public:

	URuneSpell();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ERune> RunePattern;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanBeCast;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Cast(const FSpellCastContext& Context);
};
