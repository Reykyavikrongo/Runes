#pragma once

#include "CoreMinimal.h"
#include "EffectTypes.generated.h"

UENUM(BlueprintType)
enum class EEffectType : uint8
{
    Knockback UMETA(DisplayName = "Knockback"),
    Launch    UMETA(DisplayName = "Launch"),
    Pull      UMETA(DisplayName = "Pull"),

    Slow      UMETA(DisplayName = "Slow"),
    Stun      UMETA(DisplayName = "Stun"),
    Root      UMETA(DisplayName = "Root"),

    Burn      UMETA(DisplayName = "Burn"),
    Freeze    UMETA(DisplayName = "Freeze")
};

USTRUCT(BlueprintType)
struct FEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffectType Type = EEffectType::Knockback;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Magnitude = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Direction = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FEffectContext
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Source = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Target = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ImpactLocation = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FActiveEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEffectData Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEffectContext Context;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RemainingTime = 0.f;
};