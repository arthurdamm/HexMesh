// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedRenderActor.generated.h"

USTRUCT(BlueprintType)
struct FInstanceInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	bool bIsVisible;
	
	// FLinearColor DebugColor;
	// int32 OwningShipID;

	FInstanceInfo() = default;
	
	FInstanceInfo(FTransform InTransform, bool bVisible = true)
	: Transform(InTransform), bIsVisible(bVisible)
	{}
};

UCLASS(Abstract)
class HEXMESH_API AInstancedRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInstancedRenderActor();
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	int32 AddInstance(FVector Position, const TPair<int, int>& Axial);
	virtual void ApplyCustomData(int32 InstanceIndex, const TPair<int, int>& Axial);
	void PrintInstanceData();
	void PrintInstances();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool ConstructorHelperInitAssets();
	void InitISM();
	virtual void ConfigureISM();

	virtual const TCHAR* GetMeshName() const
	{
    	return TEXT("DUMMY");
	}

	virtual const TCHAR* GetMeshAssetPath() const
	{
    	return TEXT("DUMMY");
	}

	virtual const TArray<const TCHAR*> GetMaterialAssetPaths() const
	{
    	return { TEXT("DUMMY") };
	}


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ISM")
    class UInstancedStaticMeshComponent* ISM = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ISM")
    UStaticMesh* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ISM")
	TArray<UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ISM")
    float ScaleFactor = 10.0f;

private:
	UPROPERTY()
	TMap<int32, FInstanceInfo> InstanceData;
};

