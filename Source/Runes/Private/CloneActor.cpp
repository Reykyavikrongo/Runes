// Fill out your copyright notice in the Description page of Project Settings.


#include "CloneActor.h"

// Sets default values
ACloneActor::ACloneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	// IMPORTANT: Load the skeletal mesh asset (not class)
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> QuinnMesh(
		TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple")
	);

	if (QuinnMesh.Succeeded())
	{
		Mesh->SetSkeletalMesh(QuinnMesh.Object);
	}

	// Optional but recommended defaults
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(true);

	SetReplicates(false);
}

// Called when the game starts or when spawned
void ACloneActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACloneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

