// Fill out your copyright notice in the Description page of Project Settings.

#include "LockOnComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

#include "LockOnTargetInterface.h"

ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	CachedPawn = Cast<APawn>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	CachedPC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CachedWorld = GetWorld();
	LockOnSphere = FCollisionShape::MakeSphere(MaxLockDistance);
}

void ULockOnComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AcquireTarget();
}

void ULockOnComponent::SetCurrentTarget(AActor* NewTarget)
{
	if (CurrentTarget == NewTarget)
	{
		return;
	}

	CurrentTarget = NewTarget;

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("SetCurrentTarget triggered, new target is: %s"), *CurrentTarget->GetName()));
	OnTargetChanged.Broadcast(CurrentTarget);
}

void ULockOnComponent::AcquireTarget()
{
	
	if (!CachedPawn) return;
	if (!CachedPC) return;
	if (!CachedWorld) return;

	const FVector Origin = CachedPawn->GetActorLocation();

	TArray<FOverlapResult> Overlaps;

	CachedWorld->OverlapMultiByChannel(
		Overlaps,
		Origin,
		FQuat::Identity,
		ECC_Pawn,
		LockOnSphere
	);

	AActor* BestTarget = NULL;
	int NOfValidTargets = 0;

	// lcoates the first lock onable actor in the given range, for now
	// TODO: implement enemy switching and multiple lock onable actors at once (in an array or smth)
	for (const FOverlapResult& Result : Overlaps)
	{
		AActor* Actor = Result.GetActor();
		if (!Actor) continue;

		if (!Actor->Implements<ULockOnTargetInterface>()) continue;
		if (!ILockOnTargetInterface::Execute_IsLockOnValid(Actor)) continue;

		NOfValidTargets++;

		const FVector EnemyLocation =
			Actor->GetActorLocation();

		BestTarget = Actor;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Target: %s"), *BestTarget->GetName()));
	}

	if (NOfValidTargets == 0)
	{
		SetCurrentTarget(NULL);
		return;
	}
	
	SetCurrentTarget(BestTarget);

	Distance =
		FVector::Distance(
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation(),
			CurrentTarget->GetActorLocation());

	if (BestTarget)
	{
		SetMidPoint(BestTarget->GetActorLocation());
	}
}

void ULockOnComponent::CycleTarget(float Direction)
{
	// Placeholder for later
	// Direction: -1 = left, +1 = right
	// You will re-use AcquireTarget logic but bias by screen-space X

	//AcquireTarget();
}

AActor* ULockOnComponent::GetCurrentTarget() const
{
	return CurrentTarget;
}

FVector ULockOnComponent::GetAimPoint() const
{
	if (!CurrentTarget) return FVector::ZeroVector;

	if (!CurrentTarget->Implements<ULockOnTargetInterface>())
		return FVector::ZeroVector;

	return ILockOnTargetInterface::Execute_GetLockOnLocation(CurrentTarget);
}

bool ULockOnComponent::HasTarget() const
{
	return CurrentTarget != NULL;
}

void ULockOnComponent::SetMidPoint(FVector EnemyLocation)
{
	const FVector PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	MidPoint = (PlayerLocation + EnemyLocation) * 0.5f;
}

FVector ULockOnComponent::GetCurrentTargetLockOnLocation() const
{
	if (!HasTarget())
	{
		return FVector::ZeroVector;
	}

	if (CurrentTarget->Implements<ULockOnTargetInterface>())
	{
		return ILockOnTargetInterface::Execute_GetLockOnLocation(CurrentTarget);
	}

	return CurrentTarget->GetActorLocation();
}

float ULockOnComponent::GetDistanceBetweenPlayerAndEnemy()
{
	return Distance;
}

void ULockOnComponent::SetDistanceBetweenPlayerAndEnemy(FVector EnemyLocation)
{
	Distance = FVector::Distance(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation(),
		CurrentTarget->GetActorLocation());
}

FVector ULockOnComponent::GetMidPoint() const
{
	return MidPoint;
}
