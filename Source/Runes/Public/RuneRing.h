// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rune.h"
#include "RuneRing.generated.h"

UENUM(BlueprintType)
enum class ERune : uint8
{
	Ka,
	Lo,
	Tu,
	Zi
};

UCLASS()
class RUNES_API ARuneRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuneRing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddRune(ERune RuneType);

	UFUNCTION(BlueprintCallable)
	void ClearRunes();
	
	UFUNCTION(BlueprintCallable)
	void RemoveNewestRune();

	const TArray<ERune>& GetRunes() const { return RuneArray; }

private:

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY()
	TArray<ERune> RuneArray;
	
	UPROPERTY()
	TArray<ARune*> RuneActors;

	UPROPERTY(EditAnywhere, Category="Rune Ring")
	float RingRadius = 35.0f;

	UPROPERTY(EditAnywhere, Category = "Rune Ring")
	float SpinSpeed = 130.0f;

	float CurrentAngle = 0.f;

	void RebuildRuneActors();

};
