#define MY_CLASSNAME TEXT("UHexWorldSubsystem")

#include "HexWorldSubsystem.h"
#include "HexGrid.h"
#include "HexGridRenderActor.h"
#include "Ship1RenderActor.h"
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

    if (!HexGridRenderActor)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        HexGridRenderActor = GetWorld()->SpawnActor<AHexGridRenderActor>(
            AHexGridRenderActor::StaticClass(),
            FVector(0.0f, 0.0f, 0.0f),
            FRotator::ZeroRotator,
            SpawnParams
        );

        UE_LOG(LogTemp, Warning, TEXT("SPAWNED! %p at %s"), HexGridRenderActor, *HexGridRenderActor->GetActorLocation().ToString());
    }
	if (!Ship1RenderActor)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Ship1RenderActor = GetWorld()->SpawnActor<AShip1RenderActor>(
            AShip1RenderActor::StaticClass(),
            FVector(0.0f, 0.0f, 100.0f),
            FRotator::ZeroRotator,
            SpawnParams
        );

        UE_LOG(LogTemp, Warning, TEXT("SPAWNED! %p at %s"), Ship1RenderActor, *Ship1RenderActor->GetActorLocation().ToString());
    }
}

void UHexWorldSubsystem::BuildGrid()
{
	UE_LOG(LogTemp, Log, TEXT("HexWorldSubsystem::BuildGrid"));

	if (HexGridRenderActor)
	{
		for (int q = -HexGrid::GRID_RADIUS; q <= HexGrid::GRID_RADIUS; ++q)
		{
			int r1 = FMath::Max(-HexGrid::GRID_RADIUS, -q - HexGrid::GRID_RADIUS);
			int r2 = FMath::Min(HexGrid::GRID_RADIUS, -q + HexGrid::GRID_RADIUS);

			for (int r = r1; r <= r2; ++r)
			{
				FVector WorldPosition = HexGrid::AxialToWorld(q, r);

				HexGridRenderActor->AddInstance(WorldPosition, TPair<int, int>(q, r));
				UE_LOG(LogTemp, Warning, TEXT("ADD INSTANCE at: %s"), *WorldPosition.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No HexGridActor found to render!!!"));
	}

	HexGridRenderActor->PrintInstanceData();
	HexGridRenderActor->PrintInstances();
    PlaceShips();
}

void UHexWorldSubsystem::PlaceShips()
{
	UE_LOG(LogTemp, Log, TEXT("HexWorldSubsystem::BuildGrid"));
	if (Ship1RenderActor)
	{
		Ship1RenderActor->AddInstance(HexGrid::AxialToWorld(0,0), TPair<int, int>(0, 0));
		Ship1RenderActor->AddInstance(HexGrid::AxialToWorld(2,2), TPair<int, int>(2, 2));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ship1RenderActor found to render!"));
	}
}

bool UHexWorldSubsystem::DispatchClickEvent(UInstancedStaticMeshComponent* ISM, int32 instanceIndex)
{
	
	if (AHexGridRenderActor* hexActor = Cast<AHexGridRenderActor>(ISM->GetOwner()))
	{
		LOG_CLASS("AHexGridRenderActor instanceIndex: %d", instanceIndex);
	}
	else if (AShip1RenderActor* shipActor = Cast<AShip1RenderActor>(ISM->GetOwner()))
	{
		LOG_CLASS("AShip1RenderActor instanceIndex: %d", instanceIndex);
	}
	// ISM->SetCustomDataValue(instanceIndex, 0, 0.0f, /*bMarkRenderStateDirty*/ false);
	
	return true;
}

// bool UHexWorldSubsystem::