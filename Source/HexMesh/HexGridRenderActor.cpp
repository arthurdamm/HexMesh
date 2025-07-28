// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridRenderActor.h"

AHexGridRenderActor::AHexGridRenderActor()
{
    ConstructorHelperInitAssets();
}

const TCHAR* AHexGridRenderActor::GetMeshName() const
{
    return TEXT("HexGrid");
}

const TCHAR* AHexGridRenderActor::GetMeshAssetPath() const
{
    return TEXT("/Game/SM_FlatHexTwoMaterials.SM_FlatHexTwoMaterials");
}

const TArray<const TCHAR*> AHexGridRenderActor::GetMaterialAssetPaths() const
{
    return {
        TEXT("/Game/M_HexBasic.M_HexBasic"),
        TEXT("/Game/M_HexBorder.M_HexBorder")
    };
}