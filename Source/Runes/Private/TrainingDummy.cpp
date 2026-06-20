// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainingDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ATrainingDummy::ATrainingDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_Pawn);

	LockOnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LockOnPoint"));
	LockOnPoint->SetupAttachment(Root);
	LockOnPoint->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	LockOnMarker = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnMarker"));
	LockOnMarker->SetupAttachment(Root);
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

FVector ATrainingDummy::GetLockOnLocation_Implementation() const
{
	return LockOnPoint
		? LockOnPoint->GetComponentLocation()
		: GetActorLocation();
}

bool ATrainingDummy::IsLockOnValid_Implementation() const
{
	return IsValid(this);
}

