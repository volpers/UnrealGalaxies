

#include "UnrealGalaxies.h"
#include "SolarSystem.h"
#include "SolarsystemManager.h"
#include "UnrealGalaxiesGameMode.h"
#include "UnrealGalaxiesPlayerController.h"

AUnrealGalaxiesGameMode::AUnrealGalaxiesGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = AUnrealGalaxiesPlayerController::StaticClass();
}

void AUnrealGalaxiesGameMode::SpawnComponents() {

}

void AUnrealGalaxiesGameMode::BeginPlay() {
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world) {
		//ASolarSystem* solarsystem = world->SpawnActor<ASolarSystem>(ASolarSystem::StaticClass());
		//solarsystem->CreatePlanets();
		//solarsystem->GetRootComponent()->SetWorldLocation(FVector(1.f,1.f,1.f));
		ASolarsystemManager* manager = world->SpawnActor<ASolarsystemManager>(ASolarsystemManager::StaticClass());
		manager->Init();
	}

	
}




