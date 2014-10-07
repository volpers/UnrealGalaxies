

#pragma once

#include "AssetManager.h"
#include "PlanetProperties.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"


/**
 * 
 */
UCLASS()
class APlanet : public AActor
{
	GENERATED_UCLASS_BODY()
	public:
	~APlanet();
	void BeginPlay() override;
	void Update();
	void SetAsset(UObject* asset);
	void SetProperties(FVector sunPos, const float size, const int number, const float speed, const EPlanet::Type type);
	void Rotate();
	void OrbitAround();
	private:
	FVector sunPos;
	PlanetProperties* properties;
	UObject* asset;
	TSubobjectPtr<UStaticMeshComponent> component;
	FRotator rotation;
	bool hasRings;
	bool hasMoon;
};
