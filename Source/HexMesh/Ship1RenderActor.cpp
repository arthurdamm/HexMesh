#include "Ship1RenderActor.h"
#include "ISMHexAnimator.h"
#include "HexGrid.h"

AShip1RenderActor::AShip1RenderActor()
{
    ScaleFactor = 1.0f;
    ConstructorHelperInitAssets();
}

const TCHAR* AShip1RenderActor::GetMeshName() const
{
    return TEXT("HexGrid");
}

const TCHAR* AShip1RenderActor::GetMeshAssetPath() const
{
    return TEXT("/Game/StarSparrow/Meshes/Examples/SM_StarSparrow15.SM_StarSparrow15");
}

const TArray<const TCHAR*> AShip1RenderActor::GetMaterialAssetPaths() const
{
    return {};
}

void AShip1RenderActor::BeginPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("AShip1RenderActor::BeginPlay()"));
    Super::BeginPlay();
    Animator = NewObject<UISMHexAnimator>(this);
    Animator->Init(ISM, HexGrid::HEX_RADIUS); // Use your existing ISM ptr and hex size

    Animator->AnimateToAxial(0, FIntPoint(0,0), FIntPoint(1,1), 1.0f);
    Animator->AnimateToAxial(1, FIntPoint(2,2), FIntPoint(2,4), 1.0f);
}

void AShip1RenderActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Animator) Animator->Tick(DeltaTime);
}