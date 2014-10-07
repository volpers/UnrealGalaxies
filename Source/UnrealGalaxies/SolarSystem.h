

#pragma once

#include <map>
#include "PlanetFactory.h"
#include "Logger.h"
#include "Planet.h"
#include "AssetManager.h"
#include "GameFramework/Actor.h"
#include "SolarSystem.generated.h"


/**
 * 
 */
UCLASS()
class UNREALGALAXIES_API ASolarSystem : public AActor
{
	GENERATED_UCLASS_BODY()
	
	public:
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	TSubobjectPtr<UStaticMeshComponent> sunComp;
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	TSubobjectPtr<UPointLightComponent> lightComp;
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	TSubobjectPtr<USphereComponent> collisionSphere;
	void BeginPlay() override;
	void CreateSun(const class FPostConstructInitializeProperties& PCIP);
	void CreateLight(const class FPostConstructInitializeProperties& PCIP);
	void CreateCollisionSphere();
	void CreatePlanets();
	void LoadAssets();
	void Tick(float deltaTime) override;
	UFUNCTION()
	void OnEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnLeave(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	private:
	UObject* sun;
	TArray<APlanet*> planets;
	FRotator rotation;
	const float gameSpeed;
	const int32 numPlanets;
	const float sunSize;
	float diameter;
	float timeToTick;
	float rotationSpeed;
	void RotateSun();
	
};
