

#pragma once

#include "GameFramework/GameMode.h"
#include "UnrealGalaxiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AUnrealGalaxiesGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	private:
		void SpawnComponents();
	public:
		void BeginPlay() override;
	
};
