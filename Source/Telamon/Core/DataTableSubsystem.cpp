// Copyright 2022 joaofonseca.dev

#include "DataTableSubsystem.h"
#include "DataTableSubsystemSettings.h"

bool UDataTableSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	const UDataTableSubsystemSettings* const DataTableSubsystemSettings = GetDefault<UDataTableSubsystemSettings>();

	m_InputActionDataTable = DataTableSubsystemSettings->m_InputActionDataTable;
}
