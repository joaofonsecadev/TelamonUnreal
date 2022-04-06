// Copyright 2022 joaofonseca.dev

#pragma once

#include "DataTableSubsystemSettings.generated.h"

class UDataTable;

UCLASS(Config=Game, DefaultConfig, meta = (DisplayName = "Data Tables"))
class TELAMON_API UDataTableSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditDefaultsOnly, Category = "Data Tables", meta = (DisplayName = "Input Actions"))
	TSoftObjectPtr<UDataTable> m_InputActionDataTable;
	
};
