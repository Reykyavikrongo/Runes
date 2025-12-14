// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RuneRing.h"
#include "RuneInvokerComponent.h"
#include "RunesCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ARunesCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* KaAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LoAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TuAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ZiAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RemoveRunesAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RemoveNewestRuneAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InvokeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Spell1Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Spell2Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Spell3Action;

	UPROPERTY()
	ARuneRing* RuneRing;

	UPROPERTY(VisibleAnywhere)
	URuneInvokerComponent* RuneInvoker;

public:
	ARunesCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void KaCall();
	void LoCall();
	void TuCall();
	void ZiCall();

	void ClearRunes();
	void RemoveNewestRune();

	void Invoke();
	void CastSpell1();
	void CastSpell2();
	void CastSpell3();

};

