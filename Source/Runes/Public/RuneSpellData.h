// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RuneRing.h"
#include "RuneSpell.h"
#include "RuneSpellData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RUNES_API URuneSpellData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<URuneSpell> SpellClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<ERune> RunePattern;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName SpellName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D* Icon;
};

