// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ATrainingDummy::ATrainingDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);

	LockOnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LockOnPoint"));
	LockOnPoint->SetupAttachment(GetMesh());
	LockOnPoint->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	LockOnMarker = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnMarker"));
	LockOnMarker->SetupAttachment(GetMesh());
	LockOnMarker->SetVisibility(false);

}

void ATrainingDummy::SetLockedOn(bool bLockedOn)
{
	LockOnMarker->SetVisibility(bLockedOn);
}

// Called when the game starts or when spawned
void ATrainingDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrainingDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
