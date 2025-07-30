// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "lib/InstancedRenderActor.h"
#include "HexGridRenderActor.generated.h"

/**
 * 
 */
UCLASS()
class HEXMESH_API AHexGridRenderActor : public AInstancedRenderActor
{
	GENERATED_BODY()

public:
	AHexGridRenderActor();

protected:	
	virtual const TCHAR* GetMeshName() const override;
	virtual const TCHAR* GetMeshAssetPath() const override;
	virtual const TArray<const TCHAR*> GetMaterialAssetPaths() const override;
	void ConfigureISM() override;

};
