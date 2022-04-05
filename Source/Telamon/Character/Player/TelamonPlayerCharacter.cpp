// Copyright 2022 joaofonseca.dev

#include "TelamonPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "TelamonPlayerController.h"


DEFINE_LOG_CATEGORY(LogTelamonPlayerCharacter);

ATelamonPlayerCharacter::ATelamonPlayerCharacter()
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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ATelamonPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	ATelamonPlayerController* PlayerController = Cast<ATelamonPlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTelamonPlayerCharacter, Error, TEXT("Couldn't get a valid PlayerController"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!IsValid(EnhancedInputLocalPlayerSubsystem))
	{
		UE_LOG(LogTelamonPlayerCharacter, Error, TEXT("Couldn't get a valid EnhancedInputLocalPlayerSubsystem"));
		return;
	}

	EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(m_InputMappingContext, 0);
}

void ATelamonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		UE_LOG(LogTelamonPlayerCharacter, Error, TEXT("TelamonCharacter not using Enhanced Input System"));
		return;
	}

	EnhancedInputComponent->BindAction(m_InputActions.FootMove, ETriggerEvent::Triggered, this, &ATelamonPlayerCharacter::Movement);
	EnhancedInputComponent->BindAction(m_InputActions.CameraControl, ETriggerEvent::Triggered, this, &ATelamonPlayerCharacter::CameraControl);

	EnhancedInputComponent->BindAction(m_InputActions.Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(m_InputActions.Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
}

void ATelamonPlayerCharacter::Movement(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() == 0.f || Value.GetValueType() != EInputActionValueType::Axis2D)
	{
		return;
	}
	
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector SidewardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, Value[1]);
	AddMovementInput(SidewardDirection, Value[0]);
}

void ATelamonPlayerCharacter::CameraControl(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() == 0.f || Value.GetValueType() != EInputActionValueType::Axis2D)
	{
		return;
	}
	
	AddControllerPitchInput(Value[1]);
	AddControllerYawInput(Value[0]);
}
