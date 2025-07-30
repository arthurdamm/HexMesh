#define MY_CLASSNAME TEXT("UHexWorldSubsystem")

#include "HexWorldSubsystem.h"
#include "HexGrid.h"
// #include "RenderActors/HexGridRenderActor.h"
#include "GameActors/HexGridActor.h"
#include "GameActors/Ship1Actor.h"
#include "utils/Logging.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void UHexWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    UE_LOG(LogTemp, Warning, TEXT("UHexWorldSubsystem::OnWorldBeginPlay foo"));

    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &UHexWorldSubsystem::BuildGrid, 0.1f, false);

    if (!HexGridActor)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        HexGridActor = GetWorld()->SpawnActor<AHexGridActor>(
            AHexGridActor::StaticClass(),
            FVector(0.0f, 0.0f, 0.0f),
            FRotator::ZeroRotator,
            SpawnParams
        );

        UE_LOG(LogTemp, Warning, TEXT("SPAWNED! %p at %s"), HexGridActor, *HexGridActor->GetActorLocation().ToString());
    }
	if (!Ship1Actor)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Ship1Actor = GetWorld()->SpawnActor<AShip1Actor>(
            AShip1Actor::StaticClass(),
            FVector(0.0f, 0.0f, 100.0f),
            FRotator::ZeroRotator,
            SpawnParams
        );

        UE_LOG(LogTemp, Warning, TEXT("SPAWNED! %p at %s"), Ship1Actor, *Ship1Actor->GetActorLocation().ToString());
    }
}

void UHexWorldSubsystem::BuildGrid()
{
	UE_LOG(LogTemp, Log, TEXT("HexWorldSubsystem::BuildGrid"));

	if (HexGridActor)
	{
		for (int q = -HexGrid::GRID_RADIUS; q <= HexGrid::GRID_RADIUS; ++q)
		{
			int r1 = FMath::Max(-HexGrid::GRID_RADIUS, -q - HexGrid::GRID_RADIUS);
			int r2 = FMath::Min(HexGrid::GRID_RADIUS, -q + HexGrid::GRID_RADIUS);

			for (int r = r1; r <= r2; ++r)
			{
				FVector WorldPosition = HexGrid::AxialToWorld(q, r);

				HexGridActor->AddInstance(WorldPosition, FIntPoint(q, r));
				UE_LOG(LogTemp, Warning, TEXT("ADD INSTANCE at: %s"), *WorldPosition.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No HexGridActor found to render!!!"));
	}

	// HexGridRenderActor->PrintInstanceData();
	// HexGridRenderActor->PrintInstances();
    PlaceShips();
}

void UHexWorldSubsystem::PlaceShips()
{
	UE_LOG(LogTemp, Log, TEXT("HexWorldSubsystem::BuildGrid"));
	if (Ship1Actor)
	{
		Ship1Actor->AddInstance(HexGrid::AxialToWorld(0,0), FIntPoint(0, 0));
		Ship1Actor->AddInstance(HexGrid::AxialToWorld(2,2), FIntPoint(2, 2));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ship1RenderActor found to render!"));
	}
}

bool UHexWorldSubsystem::DispatchClickEvent(UInstancedStaticMeshComponent* ISM, int32 instanceIndex)
{
	
	// if (AHexGridRenderActor* hexActor = Cast<AHexGridRenderActor>(ISM->GetOwner()))
	// {
	// 	LOG_CLASS("AHexGridRenderActor instanceIndex: %d", instanceIndex);
	// }
	// else if (AShip1RenderActor* shipActor = Cast<AShip1RenderActor>(ISM->GetOwner()))
	// {
	// 	LOG_CLASS("AShip1RenderActor instanceIndex: %d", instanceIndex);
	// }
	// ISM->SetCustomDataValue(instanceIndex, 0, 0.0f, /*bMarkRenderStateDirty*/ false);
	
	return true;
}

// bool UHexWorldSubsystem::