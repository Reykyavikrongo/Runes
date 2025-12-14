// Fill out your copyright notice in the Description page of Project Settings.


#include "Rune.h"

// Sets default values
ARune::ARune()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RuneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RuneMesh"));
	RootComponent = RuneMesh;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")
	);

	if (MeshFinder.Succeeded())
	{
		RuneMesh->SetStaticMesh(MeshFinder.Object);
		RuneMesh->SetVisibility(true, true);
		RuneMesh->SetHiddenInGame(false);
		RuneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RuneMesh->SetWorldScale3D(FVector(0.2f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatFinder(
		TEXT("/Game/StarterContent/Materials/Rune_Material.Rune_Material")
	);

	if (MatFinder.Succeeded())
	{
		RuneMesh->SetMaterial(0, MatFinder.Object);
	}
}

// Called when the game starts or when spawned
void ARune::BeginPlay()
{
	Super::BeginPlay();

	if (RuneMesh->GetMaterial(0))
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(RuneMesh->GetMaterial(0), this);
		RuneMesh->SetMaterial(0, DynamicMaterial);

		// Default color (white)
		DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::White);
		DynamicMaterial->SetScalarParameterValue("Opacity", 0.5f);
		DynamicMaterial->SetScalarParameterValue("GlowStrength", 3.f);
	}
	
}

// Called every frame
void ARune::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARune::SetRuneColor(const FLinearColor& Color)
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", Color);
	}
}

