// HexPC.cpp
#include "HexPC.h"
#include "HexISMUtils.h"
#include "Components/InstancedStaticMeshComponent.h"

void AHexPC::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;          // quality-of-life for desktop
    bEnableClickEvents = false;      // we do manual traces; set true if you want OnClicked events
    bEnableMouseOverEvents = false;  // optional
}

void AHexPC::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Classic input binding (works without Enhanced Input)
    check(InputComponent);
    InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AHexPC::OnLeftClick);
}

void AHexPC::OnLeftClick()
{
    UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick()"));
    FHitResult Hit;
    const bool bTraceComplex = true;  // helps when relying on mesh triangles
    if (!GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, bTraceComplex, Hit))
    {
        UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick !GetHitResultUnderCursorByChannel"));
        // If your project uses channels, you can also do: ECC_Visibility cast to ECollisionChannel
        // GetHitResultUnderCursorByChannel(ECC_Visibility, bTraceComplex, Hit);
        return;
    }

    if (!Hit.bBlockingHit) {
        UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick !Hit.bBlockingHit"));
        return;
    }

    UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Hit.Component.Get());
    if (!ISM)
    {
        UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick !ISM"));
        return;
    }

    // For ISM/HISM, Hit.Item holds the instance index
    const int32 InstanceIndex = Hit.Item;
    if (InstanceIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick InstanceIndex == INDEX_NONE"));
        return;
    }

    // UE_LOG(LogTemp, Warning, TEXT("AHexPC::OnLeftClick InstanceIndex %d"), InstanceIndex);
    // float color = HexISMUtils::GetPerInstanceCustomData(ISM, InstanceIndex, 0);
    // ISM->
    
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
        UE_LOG(LogTemp, Warning, TEXT("SET BLACK"));
        SetForComp.Remove(InstanceIndex);
        ISM->SetCustomDataValue(InstanceIndex, 0, 0.0f, /*bMarkRenderStateDirty*/ false);
    }

    // If you also packed color into [1..3], you can optionally set those here per click.
    // e.g., ISM->SetCustomDataValue(InstanceIndex, 1, 1.0f, false); // R
    //       ISM->SetCustomDataValue(InstanceIndex, 2, 1.0f, false); // G
    //       ISM->SetCustomDataValue(InstanceIndex, 3, 0.0f, false); // B

    ISM->MarkRenderStateDirty(); // push batched updates once
}