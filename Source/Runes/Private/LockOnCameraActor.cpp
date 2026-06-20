#include "LockOnCameraActor.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockOnComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"

ALockOnCameraActor::ALockOnCameraActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    SpringArmFreeCamBoom =
        CreateDefaultSubobject<USpringArmComponent>(
            TEXT("SpringArmFreeCamBoom"));

    SpringArmFreeCamBoom->SetupAttachment(Root);
    SpringArmFreeCamBoom->TargetArmLength = 600.f;
    SpringArmFreeCamBoom->bDoCollisionTest = false;
    SpringArmFreeCamBoom->bUsePawnControlRotation = false;

    SpringArmLockOnCamBoom =
        CreateDefaultSubobject<USpringArmComponent>(
            TEXT("SpringArmLockOnCamBoom"));

    SpringArmLockOnCamBoom->SetupAttachment(Root);
    SpringArmLockOnCamBoom->TargetArmLength = 600.f;
    SpringArmLockOnCamBoom->bDoCollisionTest = false;
    SpringArmLockOnCamBoom->bUsePawnControlRotation = false;
    
    lockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("lockOnComponent"));

    Camera =
        CreateDefaultSubobject<UCameraComponent>(
            TEXT("Camera"));

    Camera->SetupAttachment(SpringArmFreeCamBoom, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;
}

void ALockOnCameraActor::SwapCameraBooms()
{
    if (lockOnComponent->HasTarget())
    {
        Camera->AttachToComponent(
            SpringArmLockOnCamBoom,
            FAttachmentTransformRules::SnapToTargetIncludingScale,
            USpringArmComponent::SocketName
        );
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("SwapCameraBooms -> SpringArmLockOnCamBoom"));
    }
    else
    {
        Camera->AttachToComponent(
            SpringArmFreeCamBoom,
            FAttachmentTransformRules::SnapToTargetIncludingScale,
            USpringArmComponent::SocketName
        );
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("SwapCameraBooms -> SpringArmFreeCamBoom"));
    }
}

void ALockOnCameraActor::HandleTargetChanged(AActor* NewTarget)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("HandleTargetChanged"));
    SwapCameraBooms();
}

void ALockOnCameraActor::UpdateLockOnCameraBoomLocation()
{
    if (!lockOnComponent->HasTarget())
        return;

    SpringArmLockOnCamBoom->TargetArmLength = 1200.0f + sqrt(lockOnComponent->GetDistanceBetweenPlayerAndEnemy());
    SpringArmLockOnCamBoom->SetWorldLocation(lockOnComponent->GetMidPoint());
}

FVector ALockOnCameraActor::GetLockedOnTargetLocation()
{
    return TargetPoint;
}

ULockOnComponent* ALockOnCameraActor::GetLockOnComponent()

{
    return lockOnComponent;
}

void ALockOnCameraActor::BeginPlay()
{
    Super::BeginPlay();

    PC = GetWorld()->GetFirstPlayerController();

    if (lockOnComponent)
    {
        lockOnComponent->OnTargetChanged.AddDynamic(
            this,
            &ALockOnCameraActor::HandleTargetChanged
        );
    }

}

void ALockOnCameraActor::SetFocusPoints(
    const FVector& PlayerLocation,
    const FVector& TargetLocation)
{
    PlayerPoint = PlayerLocation;
    TargetPoint = TargetLocation;
}

void ALockOnCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PC)
    {
        SetActorRotation(PC->GetControlRotation());
    }

    UpdateLockOnCameraBoomLocation();

    if (lockOnComponent->HasTarget())
    {
        TargetPoint = lockOnComponent->GetCurrentTarget()->GetActorLocation();
        //GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("hasTarget true"));
    }
    else {
        //GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("hasTarget false"));
    }
}