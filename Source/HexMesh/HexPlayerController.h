#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HexPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HEXMESH_API AHexPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void OnLeftClick();
    void OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location);

    // Optional: remember which indices are highlighted per component
    TMap<TWeakObjectPtr<class UInstancedStaticMeshComponent>, TSet<int32>> Highlighted;
};
