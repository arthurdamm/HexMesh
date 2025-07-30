// Copyright Arthur Damm 2025

#define MY_CLASSNAME TEXT("AInstancedActor")

#include "InstancedActor.h"
#include "../utils/Logging.h"
#include "InstancedRenderActor.h"


// Sets default values
AInstancedActor::AInstancedActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInstancedActor::OnConstruction(const FTransform& Transform)
{
	LOG_CLASS();
	if (!(RenderActor = GetWorld()->SpawnActor<AInstancedRenderActor>(GetRenderActorClass())))
	{
		LOG_CLASS_ERR("Failed to spawn RenderActor");
		return;
	}
	RenderActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	RenderActor->SetActorRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void AInstancedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstancedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AInstancedActor::AddInstance(FVector Position, const FIntPoint& Axial)
{
	return RenderActor->AddInstance(Position, Axial);
}

void AInstancedActor::ApplyCustomData(int32 InstanceIndex, const FIntPoint& Axial)
{
	RenderActor->ApplyCustomData(InstanceIndex, Axial);
}

void AInstancedActor::PrintInstanceData()
{
	RenderActor->PrintInstanceData();
}

void AInstancedActor::PrintInstances()
{
	RenderActor->PrintInstances();
}


