// Copyright 2022 joaofonseca.dev

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataTable.h"
#include "InputActionDataRow.generated.h"

USTRUCT(BlueprintType)
struct TELAMON_API FInputActionDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
	UInputAction* InputAction;
};
