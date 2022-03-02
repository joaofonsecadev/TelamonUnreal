// Copyright 2022 joaofonseca.dev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TelamonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TELAMON_API ATelamonPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	void JumpInput();
	void StopJumpInput();
	void ForwardInput(const float Value);
	void SideInput(const float Value);
	void YawInput(const float Value);
	void PitchInput(const float Value);
};
