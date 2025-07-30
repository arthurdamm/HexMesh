// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedActor.generated.h"

class AInstancedRenderActor;

UCLASS()
class HEXMESH_API AInstancedActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInstancedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual TSubclassOf<AInstancedRenderActor> GetRenderActorClass() const PURE_VIRTUAL(AInstancedActor::GetRenderActorClass, return nullptr;);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 AddInstance(FVector Position, const FIntPoint& Axial);
	virtual void ApplyCustomData(int32 InstanceIndex, const FIntPoint& Axial);
	void PrintInstanceData();
	void PrintInstances();

	UPROPERTY()
	AInstancedRenderActor* RenderActor;
};
