// HexPC.cpp
#include "HexPlayerController.h"
#include "HexWorldSubsystem.h"
#include "Components/InstancedStaticMeshComponent.h"

void AHexPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;          // quality-of-life for desktop
    bEnableClickEvents = false;      // we do manual traces; set true if you want OnClicked events
    bEnableMouseOverEvents = false;  // optional
}

void AHexPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    // Classic input binding (works without Enhanced Input)
    check(InputComponent);
    InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AHexPlayerController::OnLeftClick);
    InputComponent->BindTouch(IE_Pressed, this, &AHexPlayerController::OnTouchPressed);
}

void AHexPlayerController::OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
    OnLeftClick(); // Call your shared click logic
}

void AHexPlayerController::OnLeftClick()
{
    UE_LOG(LogTemp, Warning, TEXT("AHexPlayerController::OnLeftClick() IRDER"));
    FHitResult Hit;
    const bool bTraceComplex = true;  // helps when relying on mesh triangles

    // if (!GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, bTraceComplex, Hit))
    if (!GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), bTraceComplex, Hit))
    {
        UE_LOG(LogTemp, Warning, TEXT("AHexPlayerController::OnLeftClick !GetHitResultUnderCursorByChannel"));
        // If your project uses channels, you can also do: ECC_Visibility cast to ECollisionChannel
        return;
    }

    if (!Hit.bBlockingHit) {
        UE_LOG(LogTemp, Warning, TEXT("AHexPlayerController::OnLeftClick !Hit.bBlockingHit"));
        return;
    }

    UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Hit.Component.Get());
    if (!ISM)
    {
        UE_LOG(LogTemp, Warning, TEXT("AHexPlayerController::OnLeftClick !ISM"));
        return;
    }

    // For ISM/HISM, Hit.Item holds the instance index
    const int32 InstanceIndex = Hit.Item;
    if (InstanceIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Error, TEXT("AHexPlayerController::OnLeftClick InstanceIndex == INDEX_NONE"));
        return;
    }

    if (UHexWorldSubsystem* hexWorldSubsystem = GetWorld()->GetSubsystem<UHexWorldSubsystem>())
    {
        hexWorldSubsystem->DispatchClickEvent(ISM, InstanceIndex);
    }

    TSet<int32>& SetForComp = Highlighted.FindOrAdd(ISM);
    const bool bNowHighlighted = !SetForComp.Contains(InstanceIndex);

    if (bNowHighlighted)
    {
        UE_LOG(LogTemp, Warning, TEXT("SET WHITE"));
        SetForComp.Add(InstanceIndex);
        ISM->SetCustomDataValue(InstanceIndex, 0, 1.0f, /*bMarkRenderStateDirty*/ false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SET BLACKsdd"));
        SetForComp.Remove(InstanceIndex);
        ISM->SetCustomDataValue(InstanceIndex, 0, 0.0f, /*bMarkRenderStateDirty*/ false);
    }

    ISM->MarkRenderStateDirty(); // push batched updates once
}