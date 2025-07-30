// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexMesh/lib/InstancedActor.h"
#include "Ship1Actor.generated.h"

UCLASS()
class HEXMESH_API AShip1Actor : public AInstancedActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShip1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual TSubclassOf<AInstancedRenderActor> GetRenderActorClass() const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
