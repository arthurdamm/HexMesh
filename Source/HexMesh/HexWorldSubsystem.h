#pragma once
#include "Subsystems/WorldSubsystem.h"
#include "HexWorldSubsystem.generated.h"

// Forward declares only
class AHexGridRenderActor;
class AHexGridActor;
class AShip1RenderActor;
class AShip1Actor;

UCLASS()
class HEXMESH_API UHexWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()
public:

    // void Initialize(FSubsystemCollectionBase& Collection);
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

    void BuildGrid();
    void PlaceShips();
    bool DispatchClickEvent(UInstancedStaticMeshComponent* ISM, int32 instanceIndex);

protected:
	UPROPERTY()
	AHexGridRenderActor* HexGridRenderActor = nullptr;

    UPROPERTY()
    AHexGridActor* HexGridActor = nullptr;

    UPROPERTY()
    AShip1RenderActor* Ship1RenderActor = nullptr;

    UPROPERTY()
    AShip1Actor* Ship1Actor = nullptr;
};