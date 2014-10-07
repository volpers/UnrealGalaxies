

#pragma once

#include "Chunk.h"
#include "SolarSystem.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "SolarsystemManager.generated.h"

/**
 * 
 */
UCLASS()
class ASolarsystemManager : public AActor
{
	GENERATED_UCLASS_BODY()
	public:
	void AddChunk(const FVector pos);
	void Init();
	private:
	const int numberChunks;
	TArray<AChunk*> chunks;
	APawn* player;
};
