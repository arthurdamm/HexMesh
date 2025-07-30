#define MY_CLASSNAME TEXT("AHexGridActor")

#include "HexGridActor.h"
#include "../utils/Logging.h"
#include "../RenderActors/HexGridRenderActor.h"


// Sets default values
AHexGridActor::AHexGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// void AHexGridActor::OnConstruction(const FTransform& Transform)
// {
// 	LOG_CLASS();
// 	if (!(RenderActor = GetWorld()->SpawnActor<AHexGridRenderActor>()))
// 	{
// 		LOG_CLASS_ERR("Failed to spawn RenderActor");
// 		return;
// 	}
// 	RenderActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
// 	RenderActor->SetActorRelativeLocation(FVector::ZeroVector);
// }

// Called when the game starts or when spawned
void AHexGridActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TSubclassOf<AInstancedRenderActor> AHexGridActor::GetRenderActorClass() const
{
	return AHexGridRenderActor::StaticClass();
}
