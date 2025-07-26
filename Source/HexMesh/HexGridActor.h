// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridActor.generated.h"

UCLASS()
class HEXMESH_API AHexGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hex Grid")
    class UInstancedStaticMeshComponent* HexMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    UStaticMesh* HexMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    float HexRadius = 101.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Grid")
    int32 GridRadius = 10;

    void GenerateHexGridISM();
	void GenerateHexGrid();

public:
	UMaterialInterface* HexMaterial;
	UMaterialInterface* HexBorderMaterial;

private:
	TMap<TPair<int, int>, int32> AxialToInstance;
    TMap<int32, TPair<int, int>> InstanceToAxial;

	void PrintAxialToInstance(const TMap<TPair<int, int>, int32> &Map);
	void PrintInstanceToAxial(const TMap<int32, TPair<int, int>> &Map);
};
