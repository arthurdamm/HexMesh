// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HexPC.generated.h"

/**
 * 
 */
UCLASS()
class HEXMESH_API AHexPC : public APlayerController
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
