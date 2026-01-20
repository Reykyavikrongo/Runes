// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneSpell_Clone.h"
#include "RunesCharacter.h"
#include "CloneActor.h"
#include "Engine/World.h"

void URuneSpell_Clone::Cast(const FSpellCastContext& Context)
{
    if (!Context.Caster) return;

    ARunesCharacter* Character = Context.Caster;

    UWorld* World = Context.Caster->GetWorld();
    if (!World) return;

    if (!ActiveClone)
    {
        FActorSpawnParameters Params;
        Params.Owner = Context.Caster;

        ActiveClone = World->SpawnActor<ACloneActor>(
            ACloneActor::StaticClass(),
            Context.Caster->GetActorTransform(),
            Params
        );

        return;
    }

    const FTransform PlayerTransform = Context.Caster->GetActorTransform();
    const FTransform CloneTransform = ActiveClone->GetActorTransform();

    Context.Caster->SetActorTransform(CloneTransform);
    ActiveClone->SetActorTransform(PlayerTransform);

    ActiveClone->Destroy();
    ActiveClone = nullptr;
}
