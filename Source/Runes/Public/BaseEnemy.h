// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LockOnTargetInterface.h"
#include "Components/WidgetComponent.h"
#include "EnemyBaseInterface.h"
#include "BaseEnemy.generated.h"

UCLASS()
class RUNES_API ABaseEnemy : public ACharacter, public IEnemyBaseInterface, public ILockOnTargetInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UEffectProcessorComponent> EffectProcessor;

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* LockOnPoint;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* LockOnMarker;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// LockOnTargetInterface
	virtual FVector GetLockOnLocation_Implementation() const override;
	virtual bool IsLockOnValid_Implementation() const override;

	void GotHit();

};
