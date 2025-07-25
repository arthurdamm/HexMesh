// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AHexGridActor::AHexGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HexMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HexMeshComponent"));
    // RootComponent = HexMeshComponent;
    SetRootComponent(HexMeshComponent);

    // Optional: Set default mesh via code (you can also do it in BP)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/SM_FlatHexTwoMaterials.SM_FlatHexTwoMaterials"));
	
    if (MeshAsset.Succeeded())
    {
        HexMesh = MeshAsset.Object;
        HexMeshComponent->SetStaticMesh(HexMesh);
    } else {
		UE_LOG(LogTemp, Warning, TEXT("AHexGridActor::AHexGridActor() failed to load HexMesh!"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("/Game/M_HexBasic.M_HexBasic"));
	if (MaterialFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material found!"));
		HexMaterial = MaterialFinder.Object;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material NOT found..."));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BorderMaterialFinder(TEXT("/Game/M_HexBorder.M_HexBorder"));
	if (BorderMaterialFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material found!"));
		HexBorderMaterial = BorderMaterialFinder.Object;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material NOT found..."));
	}

}

// Called when the game starts or when spawned
void AHexGridActor::BeginPlay()
{
	Super::BeginPlay();
	// GenerateHexGrid();
	
}

// Called every frame
void AHexGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGridActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
	GenerateHexGridISM();
}

void AHexGridActor::GenerateHexGridISM()
{
    HexMeshComponent->ClearInstances();
	// HexMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HexMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HexMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	HexMeshComponent->SetGenerateOverlapEvents(true);
	HexMeshComponent->SetMaterial(0, HexMaterial);
	HexMeshComponent->SetMaterial(1, HexBorderMaterial);
	HexMeshComponent->bSelectable = true; // Optional: for editor use

    // HexMeshComponent->SetPerInstanceCustomDataCount(5);
    HexMeshComponent->NumCustomDataFloats = 5;


    float R = HexRadius;

    int CustomDataIterator = 1;
    for (int q = -GridRadius; q <= GridRadius; ++q)
    {
        int r1 = FMath::Max(-GridRadius, -q - GridRadius);
        int r2 = FMath::Min(GridRadius, -q + GridRadius);

        for (int r = r1; r <= r2; ++r)
        {
            float x = R * 3.0f / 2.0f * q;
            float y = R * FMath::Sqrt(3.0f) * (r + q / 2.0f);
            FVector Position = FVector(x, y, 0.0f);

            FTransform InstanceTransform(FRotator::ZeroRotator, Position);
            int32 InstanceIndex = HexMeshComponent->AddInstance(InstanceTransform);
            HexMeshComponent->SetCustomDataValue(InstanceIndex, 0, CustomDataIterator % 2 ? 0.5f : 0.0f);
            HexMeshComponent->SetCustomDataValue(InstanceIndex, 1, CustomDataIterator + 0.0f);
            CustomDataIterator++;
            


			
        }
    }
}

void AHexGridActor::GenerateHexGrid()
{
    // Clean up previous components if regenerating
    TArray<UActorComponent*> ExistingHexes = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("EditorHex"));
    for (UActorComponent* Comp : ExistingHexes)
    {
        Comp->DestroyComponent();
    }

    if (!HexMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("HexMesh not assigned."));
        return;
    }

    float R = HexRadius;

    for (int q = -GridRadius; q <= GridRadius; ++q)
    {
        int r1 = FMath::Max(-GridRadius, -q - GridRadius);
        int r2 = FMath::Min(GridRadius, -q + GridRadius);

        for (int r = r1; r <= r2; ++r)
        {
            float x = R * 3.0f / 2.0f * q;
            float y = R * FMath::Sqrt(3.0f) * (r + q / 2.0f);
            FVector Position = FVector(x, y, 0.0f);

            // Dynamically create a StaticMeshComponent
            UStaticMeshComponent* HexComponent = NewObject<UStaticMeshComponent>(this);
            HexComponent->RegisterComponent(); // Make it live
            HexComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            HexComponent->SetRelativeLocation(Position);
            HexComponent->SetStaticMesh(HexMesh);
            HexComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            HexComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
            HexComponent->SetMobility(EComponentMobility::Static);
            HexComponent->ComponentTags.Add(FName("EditorHex")); // So we can clean up later
            HexComponent->SetGenerateOverlapEvents(true);
            HexComponent->bSelectable = true;
			HexMeshComponent->SetMaterial(0, HexMaterial);

#if WITH_EDITOR
            HexComponent->SetIsVisualizationComponent(false);
#endif
        }
    }
}