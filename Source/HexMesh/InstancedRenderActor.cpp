// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedRenderActor.h"
#include "GameISMUtils.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AInstancedRenderActor::AInstancedRenderActor()
{
	UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor::AInstancedRenderActor() %s %s"), *AInstancedRenderActor::StaticClass()->GetName(), *GetClass()->GetName());
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (AInstancedRenderActor::StaticClass() == GetClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor Returning"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor Continuing"));

}

bool AInstancedRenderActor::ConstructorHelperInitAssets()
{
	UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor::%s InitAssets()"), *GetClass()->GetName());

	ISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(GetMeshName());
	SetRootComponent(ISM);

	StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, GetMeshAssetPath()));
	if (!StaticMesh) {
		UE_LOG(LogTemp, Error, TEXT("AInstancedRenderActor::%s failed to load StaticMesh: %s"), *GetClass()->GetName(), GetMeshAssetPath());
		return false;
	}
    ISM->SetStaticMesh(StaticMesh);
	ISM->Rename(*FString::Printf(TEXT("%s_ISM"), GetMeshName()));

	for (const auto* MaterialAssetPath : GetMaterialAssetPaths()) {
		UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, MaterialAssetPath));
		if (!Material) {
			UE_LOG(LogTemp, Error, TEXT("AInstancedRenderActor::%s failed to load Material: %s "), *GetClass()->GetName(), MaterialAssetPath);
			return false;
		}
		Materials.Add(Material);

	}

	
	UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor Done"));
	return true;
}

// Called when the game starts or when spawned
void AInstancedRenderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstancedRenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInstancedRenderActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	// Additional setup can be done here if needed
	UE_LOG(LogTemp, Warning, TEXT("AInstancedRenderActor::OnConstruction() %s"), *GetClass()->GetName());

	InitISM();


}

void AInstancedRenderActor::InitISM()
{
	ISM->ClearInstances();

    ISM->SetCollisionEnabled(ECollisionEnabled::QueryOnly);              // no physics needed
    ISM->SetCollisionObjectType(ECC_WorldStatic);                        // typical for ISMs
    ISM->SetCollisionResponseToAllChannels(ECR_Ignore);                  // start clean
    ISM->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);       // the one we trace on
    ISM->SetGenerateOverlapEvents(false);                                // not needed for traces
	ISM->bSelectable = true; // Optional: for editor use
    ISM->NumCustomDataFloats = GameISMUtils::DEFAULT_NUM_CUSTOM_DATA_FLOATS;

	for (int32 i = 0; i < Materials.Num(); i++)
	{
		ISM->SetMaterial(i, Materials[i]);
	}

}

int32 AInstancedRenderActor::AddInstance(FVector Position, const TPair<int, int>& Axial)
{
	FTransform InstanceTransform(FRotator::ZeroRotator, Position);  
	InstanceTransform.SetScale3D(FVector(ScaleFactor));
	int32 InstanceIndex = ISM->AddInstance(InstanceTransform);

	ApplyCustomData(InstanceIndex, Axial);
	return InstanceIndex;
}

void AInstancedRenderActor::ApplyCustomData(int32 InstanceIndex, const TPair<int, int>& Axial)
{

}