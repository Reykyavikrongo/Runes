#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOnCameraActor.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class ULockOnComponent;

UCLASS()
class RUNES_API ALockOnCameraActor : public AActor
{
    GENERATED_BODY()

public:
    ALockOnCameraActor();

    virtual void Tick(float DeltaTime) override;

    void SetFocusPoints(
        const FVector& PlayerLocation,
        const FVector& TargetLocation);

    UCameraComponent* GetCamera() const
    {
        return Camera;
    }

    void SwapCameraBooms();

    UFUNCTION()
    void HandleTargetChanged(AActor* NewTarget);

    void UpdateLockOnCameraBoomLocation();

    FVector GetLockedOnTargetLocation();

    ULockOnComponent* GetLockOnComponent();
    

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USceneComponent* Root;

    APlayerController* PC;

    UPROPERTY()
    USpringArmComponent* SpringArmFreeCamBoom;

    UPROPERTY()
    USpringArmComponent* SpringArmLockOnCamBoom;

    UPROPERTY()
    ULockOnComponent* lockOnComponent;

    UPROPERTY()
    UCameraComponent* Camera;

    FVector PlayerPoint;
    FVector TargetPoint;
};