

#include "UnrealGalaxies.h"
#include "SolarsystemManager.h"
#include "Logger.h"


ASolarsystemManager::ASolarsystemManager(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), numberChunks(1), player(NULL) {
	TSubobjectPtr<USceneComponent> root = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("sceneComp"));
	RootComponent = root;
}

void ASolarsystemManager::AddChunk(FVector pos) {
	UWorld* world = GetWorld();
	if (world) {
		AChunk* chunk = world->SpawnActor<AChunk>(AChunk::StaticClass(), pos, GetActorRotation());
		//chunk->SetActorLocation(pos);
		chunk->SetCenter(pos);
		chunk->GetRootComponent()->AttachParent = RootComponent;
		chunk->Init();
		chunks.Add(chunk);
		Logger::Print("Chunk spawned!");
	}

}

void ASolarsystemManager::Init() {
	UWorld* world = GetWorld();
	if (world) {
		FConstPawnIterator it = world->GetPawnIterator();
		player = *it;
		AddChunk(player->GetActorLocation());
	}
}


