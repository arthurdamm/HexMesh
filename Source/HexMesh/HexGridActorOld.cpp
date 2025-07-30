// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridActorOld.h"
#include "GameISMUtils.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"



void AHexGridActorOld::init() {
     HexMeshComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HexMeshComponent"));
    // RootComponent = HexMeshComponent;
    SetRootComponent(HexMeshComponent);

    // const TCHAR* AssetPath = TEXT("/Game/SM_FlatHexTwoMaterials.SM_FlatHexTwoMaterials");
    // static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(GetMeshAssetPath());
	
    // if (MeshAsset.Succeeded())
    // {
    //     HexMesh = MeshAsset.Object;
    //     HexMeshComponent->SetStaticMesh(HexMesh);
    // } else {
	// 	UE_LOG(LogTemp, Warning, TEXT("AHexGridActor::AHexGridActor() failed to load HexMesh!"));
	// }

    UStaticMesh* Meshy = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, GetMeshAssetPath()));
    HexMesh = Meshy;
    HexMeshComponent->SetStaticMesh(HexMesh);

    const TCHAR* MatPath = TEXT("/Game/M_HexBasic.M_HexBasic");
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(MatPath);
	if (MaterialFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material found!"));
		HexMaterial = MaterialFinder.Object;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material NOT found..."));
	}

	// static ConstructorHelpers::FObjectFinder<UMaterialInterface> BorderMaterialFinder(TEXT("/Game/M_HexBorder.M_HexBorder"));
	// if (BorderMaterialFinder.Succeeded()) {
	// 	UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material found!"));
	// 	HexBorderMaterial = BorderMaterialFinder.Object;
	// } else {
	// 	UE_LOG(LogTemp, Warning, TEXT("UNativeTextureActorComponent Material NOT found..."));
	// }

    UMaterialInterface* Matty = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/M_HexBorder.M_HexBorder")));
    HexBorderMaterial = Matty;
    UE_LOG(LogTemp, Warning, TEXT("MATTY init!"));
}
// Sets default values
AHexGridActorOld::AHexGridActorOld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    init();
   

}

// Called when the game starts or when spawned
void AHexGridActorOld::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHexGridActorOld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGridActorOld::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
	GenerateHexGridISM();
    PrintAxialToInstance(AxialToInstance);
    PrintInstanceToAxial(InstanceToAxial);

    int32 InstanceCount = HexMeshComponent->GetInstanceCount();

    UE_LOG(LogTemp, Warning, TEXT("PRINTING INSTANCES"));
    for (int32 InstanceIndex = 0; InstanceIndex < InstanceCount; ++InstanceIndex)
    {
        FTransform InstanceTransform;
        if (HexMeshComponent->GetInstanceTransform(InstanceIndex, InstanceTransform, /*bWorldSpace=*/true))
        {
            UE_LOG(LogTemp, Log, TEXT("Instance %d: Location = %s"), 
                InstanceIndex, *InstanceTransform.GetLocation().ToString());
                HexMeshComponent->UpdateInstanceTransform(InstanceIndex, InstanceTransform, /*bWorldSpace=*/true, true);
        }

        UE_LOG(LogTemp, Log, TEXT("CustomData[%d][1] = %f"), InstanceIndex, GameISMUtils::GetPerInstanceCustomData(HexMeshComponent, InstanceIndex, 1));
        UE_LOG(LogTemp, Log, TEXT("CustomData[%d][0] = %f"), InstanceIndex, GameISMUtils::GetPerInstanceCustomData(HexMeshComponent, InstanceIndex, 0));
    }
}

void AHexGridActorOld::GenerateHexGridISM()
{
    AxialToInstance.Reset();
    InstanceToAxial.Reset();

    HexMeshComponent->ClearInstances();

    HexMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);              // no physics needed
    HexMeshComponent->SetCollisionObjectType(ECC_WorldStatic);                        // typical for ISMs
    HexMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);                  // start clean
    HexMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);       // the one we trace on
    HexMeshComponent->SetGenerateOverlapEvents(false);                                // not needed for traces
/*
    HexMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HexMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
*/
    
	HexMeshComponent->SetMaterial(0, HexMaterial);
	HexMeshComponent->SetMaterial(1, HexBorderMaterial);
	HexMeshComponent->bSelectable = true; // Optional: for editor use
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
            InstanceTransform.SetScale3D(FVector(HexScaleFactor));
            int32 InstanceIndex = HexMeshComponent->AddInstance(InstanceTransform);

            HexMeshComponent->SetCustomDataValue(InstanceIndex, 0, 0.f);
            HexMeshComponent->SetCustomDataValue(InstanceIndex, 1, CustomDataIterator + 0.0f);


            AxialToInstance.Add(TPair<int, int>(q, r), InstanceIndex);
            InstanceToAxial.Add(InstanceIndex, TPair<int, int>(q, r));
            CustomDataIterator++;
        }
    }
}

void AHexGridActorOld::PrintAxialToInstance(const TMap<TPair<int, int>, int32> &Map)
{
    for (const TPair<TPair<int, int>, int32>& Entry : Map) {
        const TPair<int, int>& Axial = Entry.Key;
        int32 InstanceId = Entry.Value;
        UE_LOG(LogTemp, Warning, TEXT("\tAxial [%d, %d] => %d"), Axial.Key, Axial.Value, InstanceId);
    }
}

void AHexGridActorOld::PrintInstanceToAxial(const TMap<int32, TPair<int, int>> &Map)
{
    for (const TPair<int32, TPair<int, int>>& Entry : Map) {
        int32 InstanceId = Entry.Key;
        const TPair<int, int>& Axial = Entry.Value;
        UE_LOG(LogTemp, Warning, TEXT("\tInstanceId %d => [%d, %d] "), InstanceId, Axial.Key, Axial.Value);
    }
}

void AHexGridActorOld::GenerateHexGrid()
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
            HexComponent->SetWorldScale3D(FVector(HexScaleFactor));
            HexComponent->SetStaticMesh(HexMesh);
            HexComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            HexComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
            HexComponent->SetMobility(EComponentMobility::Static);
            HexComponent->ComponentTags.Add(FName("EditorHex")); // So we can clean up later
            HexComponent->SetGenerateOverlapEvents(true);
            HexComponent->bSelectable = true;
			HexMeshComponent->SetMaterial(0, HexMaterial);
            HexMeshComponent->SetMaterial(1, HexBorderMaterial);

#if WITH_EDITOR
            HexComponent->SetIsVisualizationComponent(false);
#endif
        }
    }
}

