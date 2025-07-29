#pragma once

#include "CoreMinimal.h"
#include "HexSelectionState.generated.h"

UENUM(BlueprintType)
enum class EHexSelectionState : uint8
{
	WaitingForSource      UMETA(DisplayName = "Waiting for Source"),
	WaitingForDestination UMETA(DisplayName = "Waiting for Destination"),
};
