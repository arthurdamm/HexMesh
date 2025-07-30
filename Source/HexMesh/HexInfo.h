#pragma once
#include "CoreMinimal.h"
#include "HexInfo.generated.h"

USTRUCT(BlueprintType)
struct FHexInfo
{
	GENERATED_BODY()

	// UPROPERTY()
	// AShipActor* OccupyingShip = nullptr;

	UPROPERTY()
	bool bHasAsteroid = false;
	
};