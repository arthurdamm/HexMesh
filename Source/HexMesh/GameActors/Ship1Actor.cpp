#define MY_CLASSNAME TEXT("AShip1Actor")

#include "Ship1Actor.h"
#include "../utils/Logging.h"
#include "../RenderActors/Ship1RenderActor.h"


// Sets default values
AShip1Actor::AShip1Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TSubclassOf<AInstancedRenderActor> AShip1Actor::GetRenderActorClass() const
{
	LOG_CLASS();
	return AShip1RenderActor::StaticClass();
}

// Called when the game starts or when spawned
void AShip1Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

