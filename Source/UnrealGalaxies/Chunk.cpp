

#include "UnrealGalaxies.h"
#include "Chunk.h"
#include "Logger.h"


AChunk::AChunk(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), numberSystems(25), maxSize(20000)// maxSize(25000)
{
	TSubobjectPtr<USceneComponent> root = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("sceneComp"));
	RootComponent = root;
}

void AChunk::SetCenter(const FVector& v) {
	this->center = v;
}

void AChunk::Init() {
	for (int32 i = 0; i < numberSystems; i++) {
		CreateSolarSystem();
	}
}

void AChunk::CreateSolarSystem()
{
	int32 x = FMath::RandRange(-maxSize/2, maxSize/2);
	int32 y = FMath::RandRange(-maxSize/2, maxSize/2);
	int32 z = FMath::RandRange(-maxSize/2, maxSize);
	FVector position = FVector(x, y, z);

	UWorld* world = GetWorld();
	if (world) {
		ASolarSystem* system = world->SpawnActor<ASolarSystem>(ASolarSystem::StaticClass(), position, GetActorRotation());
		system->CreatePlanets();
		system->CreateCollisionSphere();
		system->GetRootComponent()->AttachParent = RootComponent;
		solarSystems.Add(position, system);
		Logger::Print("Solarsystem spawned at: ");
		Logger::Print(position);
	}
}



