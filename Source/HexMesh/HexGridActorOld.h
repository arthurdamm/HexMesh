// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridActorOld.generated.h"

UCLASS()
class HEXMESH_API AHexGridActorOld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGridActorOld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hex Grid")
    class UHierarchicalInstancedStaticMeshComponent* HexMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    UStaticMesh* HexMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    float HexScaleFactor = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    float HexRadius = 100.0f * HexScaleFactor + 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    int32 GridRadius = 10;

    void GenerateHexGridISM();
	void GenerateHexGrid();

	void init(); 
	virtual const TCHAR* GetMeshAssetPath() const
	{
    	return TEXT("/Game/SM_FlatHexTwoMaterials.SM_FlatHexTwoMaterials");
	}

public:
	UMaterialInterface* HexMaterial;
	UMaterialInterface* HexBorderMaterial;

private:
	TMap<TPair<int, int>, int32> AxialToInstance;
    TMap<int32, TPair<int, int>> InstanceToAxial;

	void PrintAxialToInstance(const TMap<TPair<int, int>, int32> &Map);
	void PrintInstanceToAxial(const TMap<int32, TPair<int, int>> &Map);
};
