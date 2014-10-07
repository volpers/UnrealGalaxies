

#include "UnrealGalaxies.h"
#include "Planet.h"
#include "Logger.h"
#include "PlanetFactory.h"


APlanet::APlanet(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), sunPos(FVector(0.f, 0.f, 0.f)), hasMoon(false), hasRings(false)
{
	component = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PlanetComp"));
	this->RootComponent = component;
	this->properties = new PlanetProperties();
	this->rotation = component->GetComponentRotation();
	//PrimaryActorTick.bCanEverTick = true;
}

APlanet::~APlanet() {
	delete this->properties;
}

void APlanet::BeginPlay() {

}

void APlanet::SetAsset(UObject* asset) {
	component->SetStaticMesh(Cast<UStaticMesh>(asset));
	component->bOwnerNoSee = false;
	component->bCastDynamicShadow = true;
	component->CastShadow = true;
	component->BodyInstance.SetObjectType(ECC_WorldDynamic);
	//sunComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	component->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
	component->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);
	component->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Block);
	component->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Block);
	component->SetHiddenInGame(false);
}
/*
void APlanet::LoadAssets() {
	AssetManager::CreateObjectLibrary<UStaticMesh>(EMeshType::StaticMesh, FString(TEXT("/Game/Meshes/Planets")));
	this->asset = AssetManager::LoadAsset(AssetManager::GetObjectLibraries()[EMeshType::StaticMesh], FName(TEXT("Sun")));
}*/

void APlanet::SetProperties(FVector sunPos, float size, int number, float speed, EPlanet::Type type) {
	this->properties->size = size;
	this->properties->number = number;
	this->properties->type = type;
	this->properties->speed = speed;
	this->properties->orbitSpeed = speed * 10;
	this->sunPos = sunPos;
	this->rotation.Yaw -= speed;
	
	FString name;  
	switch (type) {
		case EPlanet::DEAD:
			name = FString(TEXT("dead"));
			break;
		case EPlanet::DESERT:
			name = FString(TEXT("desert"));
			break;
		case EPlanet::EARTHEN:
			name = FString(TEXT("earthen"));
			break;
		case EPlanet::GAS:
			name = FString(TEXT("gas"));
			break;
		case EPlanet::ICE:
			name = FString(TEXT("ice"));
			break;
		case EPlanet::VULCANIC:
			name = FString(TEXT("vulcanic"));
			break;
		case EPlanet::MOON:
			name = FString(TEXT("moon"));
			break;
		default:
			name = FString(TEXT("earthen"));
	}

	float value = FMath::FRand();
	if (value <= 0.25f && type != EPlanet::MOON) {
		hasRings = true;
		name += TEXT("_wRings");
	}

 /*	if (!hasRings && type != EPlanet::MOON) {
		Logger::Print("Moon!");
		value = FMath::Rand();
		if (value <= 0.25f) {
			hasMoon = true;
			APlanet* moon = PlanetFactory::CreateSpecific(this, EPlanet::MOON);
			moon->GetRootComponent()->AttachParent = RootComponent;
		}
	}*/	

	UObject* asset = AssetManager::LoadAsset(AssetManager::GetObjectLibraries()[EMeshType::StaticMesh], FName(*name));
	this->SetAsset(asset);
	this->SetActorScale3D(FVector(size, size, size));

}

void APlanet::Update() {
	Rotate();
	OrbitAround();
}

void APlanet::Rotate() {
	FTransform transform = component->GetComponentTransform();
	transform.ConcatenateRotation(rotation.Quaternion());
	transform.NormalizeRotation();
	component->SetWorldTransform(transform);
}

void APlanet::OrbitAround() {
	const FVector oldPosition = GetActorLocation();
	const FQuat quaternion(FVector::UpVector, FMath::DegreesToRadians(properties->speed));
	FVector direction = oldPosition - sunPos;
	direction = quaternion * direction;
	const FVector newPos = sunPos + direction;
	SetActorLocation(newPos);
}

//void APlanet::Tick(float deltaTime) {
	
//}





