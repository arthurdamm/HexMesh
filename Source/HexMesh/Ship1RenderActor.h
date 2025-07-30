// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "lib/InstancedRenderActor.h"
#include "Ship1RenderActor.generated.h"

class UISMHexAnimator;

/**
 * 
 */
UCLASS()
class HEXMESH_API AShip1RenderActor : public AInstancedRenderActor
{
	GENERATED_BODY()

public:
	AShip1RenderActor();

	virtual void Tick(float DeltaTime) override;

	UISMHexAnimator* Animator = nullptr;

protected:	
	virtual const TCHAR* GetMeshName() const override;
	virtual const TCHAR* GetMeshAssetPath() const override;
	virtual const TArray<const TCHAR*> GetMaterialAssetPaths() const override;

	virtual void BeginPlay() override;
};
