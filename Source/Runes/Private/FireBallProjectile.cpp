// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBallProjectile.h"
#include "EffectTypes.h"
#include "EffectProcessorComponent.h"
#include "BaseEnemy.h"

// Sets default values
AFireBallProjectile::AFireBallProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root = collision (IMPORTANT)
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetGenerateOverlapEvents(true);

	Collision->OnComponentHit.AddDynamic(this, &AFireBallProjectile::OnHit);

	// Mesh (visual only)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(
		TEXT("/Engine/BasicShapes/Sphere.Sphere")
	);

	if (SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
	}

	Mesh->SetWorldScale3D(FVector(0.25f));

	// Movement
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovement"));

	projectileMovement->SetUpdatedComponent(Collision);
	projectileMovement->InitialSpeed = 2000.f;
	projectileMovement->MaxSpeed = 2000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->ProjectileGravityScale = 0.f;

	SetReplicates(false);
}

// Called when the game starts or when spawned
void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AFireBallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::DistSquared(StartLocation, GetActorLocation()) >
		FMath::Square(MaxDistance))
	{
		Destroy();
	}
}

void AFireBallProjectile::OnHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("if (OtherActor && OtherActor != this)"));
		if (UEffectProcessorComponent* Processor =
			OtherActor->FindComponentByClass<UEffectProcessorComponent>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("FindComponentByClass<UEffectProcessorComponent>()"));
			FEffectData Effect;
			Effect.Type = EEffectType::Knockback;
			Effect.Magnitude = 1000.f;
			Effect.Direction = GetActorForwardVector();

			FEffectContext Context;
			Context.Source = GetOwner();
			Context.Target = OtherActor;
			Context.ImpactLocation = Hit.ImpactPoint;

			Cast<ABaseEnemy>(OtherActor)->GotHit();

			Processor->ReceiveEffect(Effect, Context);
		}
		Destroy();
	}
}
