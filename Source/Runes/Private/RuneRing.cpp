#include "RuneRing.h"
#include "Rune.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
ARuneRing::ARuneRing()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root scene component so attachments work
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

// Called when the game starts or when spawned
void ARuneRing::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ARuneRing::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentAngle += SpinSpeed * DeltaTime;

    const int32 Count = RuneActors.Num();
    if (Count == 0) return;

    for (int32 i = 0; i < Count; ++i)
    {
        ARune* Rune = RuneActors[i];
        if (!Rune) continue;

        float AngleDeg = CurrentAngle + (360.f / Count) * i;
        float AngleRad = FMath::DegreesToRadians(AngleDeg);

        FVector Offset(
            FMath::Cos(AngleRad) * RingRadius,
            FMath::Sin(AngleRad) * RingRadius,
            0
        );

        Rune->SetActorRelativeLocation(Offset);
    }
}

void ARuneRing::AddRune(ERune RuneType)
{
    // FIFO behavior
    if (RuneArray.Num() >= 4)
    {
        RuneArray.RemoveAt(0);

        if (RuneActors.Num() > 0)
        {
            RuneActors[0]->Destroy();
            RuneActors.RemoveAt(0);
        }
    }

    RuneArray.Add(RuneType);

    RebuildRuneActors();
}

void ARuneRing::ClearRunes()
{
    RuneArray.Empty();

    for (ARune* Rune : RuneActors)
    {
        if (Rune) Rune->Destroy();
    }

    RuneActors.Empty();
}

void ARuneRing::RemoveNewestRune()
{
    if (RuneArray.Num() == 0)
        return;

    // Remove last rune in FIFO array (LIFO behavior)
    RuneArray.RemoveAt(RuneArray.Num() - 1);

    // Destroy last actor
    if (RuneActors.Num() > 0)
    {
        ARune* LastRune = RuneActors.Last();
        if (LastRune)
            LastRune->Destroy();

        RuneActors.RemoveAt(RuneActors.Num() - 1);
    }

    // Rebuild positions
    CurrentAngle = 0.f;
}

void ARuneRing::RebuildRuneActors()
{
    // Remove old runes
    for (ARune* Rune : RuneActors)
    {
        if (Rune) Rune->Destroy();
    }
    RuneActors.Empty();

    // Spawn new runes
    for (int32 i = 0; i < RuneArray.Num(); i++)
    {
        FActorSpawnParameters Params;
        Params.Owner = this;

        ARune* Rune = GetWorld()->SpawnActor<ARune>(
            ARune::StaticClass(),
            GetTransform(),
            Params
        );

        // Attach to our RootComponent so relative offsets work
        Rune->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        FLinearColor RuneColor;

        switch (RuneArray[i])
        {
        case ERune::Ka: RuneColor = FLinearColor(3.f, 0.2f, 0.2f); break;
        case ERune::Lo: RuneColor = FLinearColor(0.2f, 0.4f, 3.f); break;
        case ERune::Tu: RuneColor = FLinearColor(0.2f, 3.f, 0.2f); break;
        case ERune::Zi: RuneColor = FLinearColor(3.f, 3.f, 0.2f); break;
        default: RuneColor = FLinearColor::White; break;
        }

        Rune->SetRuneColor(RuneColor);

        RuneActors.Add(Rune);

        //GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green,
        //    FString::Printf(TEXT("Spawned Rune at: %s"), *Rune->GetActorLocation().ToString()));
    }
}
