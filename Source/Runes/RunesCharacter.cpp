// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunesCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ARunesCharacter

ARunesCharacter::ARunesCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	RuneInvoker = CreateDefaultSubobject<URuneInvokerComponent>(TEXT("RuneInvoker"));

	static ConstructorHelpers::FObjectFinder<UInputAction> Ka(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Ka_Action.Ka_Action'")
	);
	if (Ka.Succeeded())
		KaAction = Ka.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Lo(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Lo_Action.Lo_Action'")
	);
	if (Lo.Succeeded())
		LoAction = Lo.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Tu(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Tu_Action.Tu_Action'")
	);
	if (Tu.Succeeded())
		TuAction = Tu.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Zi(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Zi_Action.Zi_Action'")
	);
	if (Zi.Succeeded())
		ZiAction = Zi.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> RemoveRunes(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Clear_Runes_Action.Clear_Runes_Action'")
	);
	if (RemoveRunes.Succeeded())
		RemoveRunesAction = RemoveRunes.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> RemoveNewestRune(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Remove_Newest_Rune_Action.Remove_Newest_Rune_Action'")
	);
	if (RemoveNewestRune.Succeeded())
		RemoveNewestRuneAction = RemoveNewestRune.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Invoke(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Invoke_Action.Invoke_Action'")
	);
	if (Invoke.Succeeded())
		InvokeAction = Invoke.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Spell1(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Spell_Action1.Spell_Action1'")
	);
	if (Spell1.Succeeded())
		Spell1Action = Spell1.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Spell2(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Spell_Action2.Spell_Action2'")
	);
	if (Spell2.Succeeded())
		Spell2Action = Spell2.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> Spell3(
		TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/Spell_Action3.Spell_Action3'")
	);
	if (Spell3.Succeeded())
		Spell3Action = Spell3.Object;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ARunesCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	RuneRing = GetWorld()->SpawnActor<ARuneRing>();
	RuneRing->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("spine_03"));
	RuneRing->SetActorRelativeLocation(FVector(10, -30, 0));
	RuneRing->SetActorRelativeRotation(FRotator(0.f, 0.f, 90.f));

	RuneInvoker->Initialize(RuneRing);
}

void ARunesCharacter::KaCall()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Ka!"));
	RuneRing->AddRune(ERune::Ka);
}

void ARunesCharacter::LoCall()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Lo!"));
	RuneRing->AddRune(ERune::Lo);
}

void ARunesCharacter::TuCall()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Tu!"));
	RuneRing->AddRune(ERune::Tu);
}

void ARunesCharacter::ZiCall()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Zi!"));
	RuneRing->AddRune(ERune::Zi);
}

void ARunesCharacter::ClearRunes()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cleared Runes"));
	RuneRing->ClearRunes();
}

void ARunesCharacter::RemoveNewestRune()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Removed Newest Rune"));
	RuneRing->RemoveNewestRune();
}

void ARunesCharacter::Invoke()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Invoked"));
	RuneInvoker->InvokeSpell();
}

void ARunesCharacter::CastSpell1()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpellCast 1"));
	
	
	if (RuneInvoker->GetInvokedSpells().Num() >= 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("There is at least 1 spell in the spell slots"));
		RuneInvoker->GetInvokedSpells()[0]->Cast(this);
	}
}

void ARunesCharacter::CastSpell2()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpellCast 2"));

	if (RuneInvoker->GetInvokedSpells().Num() >= 2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("There is at least 2 spells in the spell slots"));
		RuneInvoker->GetInvokedSpells()[1]->Cast(this);
	}
}

void ARunesCharacter::CastSpell3()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpellCast 3"));

	if (RuneInvoker->GetInvokedSpells().Num() >= 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("There is at least 3 spells in the spell slots"));
		RuneInvoker->GetInvokedSpells()[2]->Cast(this);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARunesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunesCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARunesCharacter::Look);

		// Rune Calling
		EnhancedInputComponent->BindAction(KaAction, ETriggerEvent::Started, this, &ARunesCharacter::KaCall);
		EnhancedInputComponent->BindAction(LoAction, ETriggerEvent::Started, this, &ARunesCharacter::LoCall);
		EnhancedInputComponent->BindAction(TuAction, ETriggerEvent::Started, this, &ARunesCharacter::TuCall);
		EnhancedInputComponent->BindAction(ZiAction, ETriggerEvent::Started, this, &ARunesCharacter::ZiCall);
		
		EnhancedInputComponent->BindAction(RemoveRunesAction, ETriggerEvent::Started, this, &ARunesCharacter::ClearRunes);
		EnhancedInputComponent->BindAction(RemoveNewestRuneAction, ETriggerEvent::Started, this, &ARunesCharacter::RemoveNewestRune);


		EnhancedInputComponent->BindAction(InvokeAction, ETriggerEvent::Started, this, &ARunesCharacter::Invoke);
		EnhancedInputComponent->BindAction(Spell1Action, ETriggerEvent::Started, this, &ARunesCharacter::CastSpell1);
		EnhancedInputComponent->BindAction(Spell2Action, ETriggerEvent::Started, this, &ARunesCharacter::CastSpell2);
		EnhancedInputComponent->BindAction(Spell3Action, ETriggerEvent::Started, this, &ARunesCharacter::CastSpell3);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARunesCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ARunesCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}