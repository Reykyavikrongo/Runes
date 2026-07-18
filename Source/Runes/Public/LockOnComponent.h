// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnTargetChanged,
	AActor*,
	NewTarget);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNES_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULockOnComponent();

	void AcquireTarget();
	void CycleTarget(float Direction);

	AActor* GetCurrentTarget() const;
	FVector GetAimPoint() const;

	bool HasTarget() const;

	FVector GetMidPoint() const;
	void SetMidPoint(FVector EnemyLocation);

	FVector GetCurrentTargetLockOnLocation() const;
	float GetDistanceBetweenPlayerAndEnemy();
	void SetDistanceBetweenPlayerAndEnemy(FVector EnemyLocation);

	/*
	 * Fires whenever CurrentTarget changes.
	 * NewTarget == nullptr means lock-on ended.
	 */
	UPROPERTY(BlueprintAssignable, Category = "LockOn")
	FOnTargetChanged OnTargetChanged;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	APlayerController* CachedPC = NULL;
	APawn* CachedPawn = NULL;
	UWorld* CachedWorld = NULL;
	FVector2D CachedScreenCenter = FVector2D::ZeroVector;
	FCollisionShape LockOnSphere;

	void SetCurrentTarget(AActor* NewTarget);

private:

	UPROPERTY()
	AActor* CurrentTarget = NULL;

	FVector MidPoint;

	float MaxLockDistance = 2000.f;

	float Distance = 0.f;
};