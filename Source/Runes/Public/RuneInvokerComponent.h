// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RuneSpell.h"
#include "RuneInvokerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNES_API URuneInvokerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<class URuneSpell*> InvokedSpells;

	UPROPERTY()
	class ARuneRing* RuneRing;

public:
	void Initialize(ARuneRing* InRuneRing);

	UFUNCTION(BlueprintCallable)
	void InvokeSpell();

	const TArray<URuneSpell*>& GetInvokedSpells() const;
};
