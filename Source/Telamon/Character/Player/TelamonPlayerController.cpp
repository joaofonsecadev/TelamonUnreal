// Copyright 2022 joaofonseca.dev


#include "TelamonPlayerController.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void ATelamonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATelamonPlayerController::JumpInput);
	InputComponent->BindAction("Jump", IE_Released, this, &ATelamonPlayerController::StopJumpInput);
	
	InputComponent->BindAxis("Move Forward / Backward", this, &ATelamonPlayerController::ForwardInput);
	InputComponent->BindAxis("Move Right / Left", this, &ATelamonPlayerController::SideInput);
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &ATelamonPlayerController::YawInput);
	InputComponent->BindAxis("Look Up / Down Mouse", this, &ATelamonPlayerController::PitchInput);
}

void ATelamonPlayerController::JumpInput()
{
	ACharacter* PlayerCharacter = GetCharacter();
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->Jump();
	}
}

void ATelamonPlayerController::StopJumpInput()
{
	ACharacter* PlayerCharacter = GetCharacter();
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->StopJumping();
	}
}

void ATelamonPlayerController::ForwardInput(const float Value)
{
	ACharacter* PlayerCharacter = GetCharacter();
	if (IsValid(PlayerCharacter) && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		PlayerCharacter->AddMovementInput(Direction, Value);
	}
}

void ATelamonPlayerController::SideInput(const float Value)
{
	ACharacter* PlayerCharacter = GetCharacter();
	if (IsValid(PlayerCharacter) && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		PlayerCharacter->AddMovementInput(Direction, Value);
	}
}

void ATelamonPlayerController::YawInput(const float Value)
{
	if (Value != 0.f)
	{
		AddYawInput(Value);
	}
}

void ATelamonPlayerController::PitchInput(const float Value)
{
	if (Value != 0.f)
	{
		AddPitchInput(Value);
	}
}
