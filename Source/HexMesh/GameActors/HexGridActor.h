// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../lib/InstancedActor.h"
#include "HexGridActor.generated.h"

class AInstancedRenderActor;

UCLASS()
class HEXMESH_API AHexGridActor : public AInstancedActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHexGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// virtual void OnConstruction(const FTransform& Transform) override;

	virtual TSubclassOf<AInstancedRenderActor> GetRenderActorClass() const override;
	// {
	// 	return AInstancedRenderActor::StaticClass();
	// }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
