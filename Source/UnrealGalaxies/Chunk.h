

#pragma once

#include "GameFramework/Actor.h"
#include "Solarsystem.h"
#include "Chunk.generated.h"

/**
 * 
 */
UCLASS()
class AChunk : public AActor
{
	GENERATED_UCLASS_BODY()
	public:
	void Init();
	void SetCenter(const FVector& v);
	private:
	const int numberSystems;
	const int maxSize;
	FVector boundStart, boundHeight, boundDepth;
	FVector center;
	TMap<FVector, ASolarSystem*> solarSystems;
	void CreateSolarSystem();
};
