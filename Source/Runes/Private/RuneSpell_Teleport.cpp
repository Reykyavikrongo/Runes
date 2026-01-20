// Fill out your copyright notice in the Description page of Project Settings.

#include "RuneSpell_Teleport.h"
#include "RunesCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

void URuneSpell_Teleport::Cast(const FSpellCastContext& Context)
{
    if (!Context.Caster)
        return;

    ARunesCharacter* Character = Context.Caster;

    UWorld* World = Character->GetWorld();
    if (!World) return;

    FVector Start = Character->GetActorLocation();
    FVector Forward = Character->GetActorForwardVector();
    FVector End = Start + Forward * TeleportDistance;

    UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
    if (!Capsule) return;

    float Radius = Capsule->GetScaledCapsuleRadius();
    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    FCollisionShape CapsuleShape =
        FCollisionShape::MakeCapsule(Radius, HalfHeight);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Character);

    FHitResult Hit;

    bool bHit = World->SweepSingleByChannel(
        Hit,
        Start,
        End,
        FQuat::Identity,
        ECC_WorldStatic,
        CapsuleShape,
        QueryParams
    );

    FVector TargetLocation = bHit ? Hit.Location : End;

    Character->TeleportTo(
        TargetLocation,
        Character->GetActorRotation(),
        false,
        true
    );
}

