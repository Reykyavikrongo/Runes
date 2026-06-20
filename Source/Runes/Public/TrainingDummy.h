// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "LockOnTargetInterface.h"
#include "TrainingDummy.generated.h"

UCLASS()
class RUNES_API ATrainingDummy : public AActor, public ILockOnTargetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainingDummy();

	void SetLockedOn(bool bLockedOn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* LockOnPoint;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* LockOnMarker;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// LockOnTargetInterface
	virtual FVector GetLockOnLocation_Implementation() const override;
	virtual bool IsLockOnValid_Implementation() const override;

};
