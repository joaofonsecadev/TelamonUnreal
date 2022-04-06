// Copyright 2022 joaofonseca.dev

#pragma once

#include "Telamon/Input/InputActionDataRow.h"
#include "DataTableSubsystem.generated.h"

class UObject;
class UDataTable;
class FSubsystemCollectionBase;

UCLASS()
class TELAMON_API UDataTableSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UDataTableSubsystem() : Super() { }

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const UDataTable* GetInputActionTable() const { return m_InputActionDataTable.Get(); }

private:
	TSoftObjectPtr<UDataTable> m_InputActionDataTable;
};
