#pragma once
#include "Subsystems/WorldSubsystem.h"
#include "HexWorldSubsystem.generated.h"

// Forward declares only
class AHexGridRenderActor;
class AShip1RenderActor;

UCLASS()
class HEXMESH_API UHexWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()
public:

    // void Initialize(FSubsystemCollectionBase& Collection);
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

    void BuildGrid();
    void PlaceShips();

protected:
	UPROPERTY()
	AHexGridRenderActor* HexGridRenderActor = nullptr;

    UPROPERTY()
    AShip1RenderActor* Ship1RenderActor = nullptr;
};