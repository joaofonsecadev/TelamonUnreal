// Copyright 2022 joaofonseca.dev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TelamonPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTelamonPlayerCharacter, Warning, All);

USTRUCT()
struct FInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* FootMove = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* CameraControl = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Jump = nullptr;
	
};

UCLASS(config=Game)
class ATelamonPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ATelamonPlayerCharacter();
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	

private:
	void Movement(const FInputActionValue& Value);
	void CameraControl(const FInputActionValue& Value);

public:
	// Temporary until a cleaner solution is made
	UPROPERTY(EditDefaultsOnly, Category = "Input Setup")
	FInputActions m_InputActions;

	UPROPERTY(EditDefaultsOnly, Category = "Input Setup")
	UInputMappingContext* m_InputMappingContext;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};

