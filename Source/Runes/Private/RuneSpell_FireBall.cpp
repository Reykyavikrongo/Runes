// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_FireBall.h"
#include "RunesCharacter.h"
#include "FireBallProjectile.h"
#include "Engine/World.h"

void URuneSpell_FireBall::Cast(const FSpellCastContext& Context)
{
    //nothing yet
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FireBall casted"));

    if (!Context.Caster) return;

    ARunesCharacter* Character = Context.Caster;

    UWorld* World = Context.Caster->GetWorld();
    if (!World) return;

	const FVector Forward = Context.Caster->GetActorForwardVector();

	const FVector SpawnLocation =
		Context.Caster->GetActorLocation() +
		Forward * 150.f;

	const FRotator SpawnRotation =
		Context.Caster->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = Context.Caster;
	Params.SpawnCollisionHandlingOverride =
	ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AFireBallProjectile>(
		AFireBallProjectile::StaticClass(),
		SpawnLocation,
		SpawnRotation,
		Params
	);


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FireBall spawned"));
}
