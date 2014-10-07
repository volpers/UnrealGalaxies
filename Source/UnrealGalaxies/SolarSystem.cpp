

#include "UnrealGalaxies.h"
#include "SolarSystem.h"


ASolarSystem::ASolarSystem(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), gameSpeed(0.033f), rotationSpeed(0.1f), numPlanets(5), sunSize(1.f), diameter(0.f)
{
	TSubobjectPtr<USceneComponent> root = PCIP.CreateDefaultSubobject<USceneComponent>(this, "Root");
	RootComponent = root;
	this->timeToTick = gameSpeed;
	PrimaryActorTick.bCanEverTick = true;
	LoadAssets();
	CreateLight(PCIP);
	CreateSun(PCIP);
	collisionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, "CollisionSpehre");
	collisionSphere->AttachParent = RootComponent;
}

void ASolarSystem::CreateLight(const class FPostConstructInitializeProperties& PCIP) {
	lightComp = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "LightComp");
	lightComp->Intensity = 1000000.f;
	lightComp->SourceRadius = 200.f;
	lightComp->AttenuationRadius = 5000.f;
	lightComp->bVisible = true;
	lightComp->AttachParent = RootComponent;
}


void ASolarSystem::CreateSun(const class FPostConstructInitializeProperties& PCIP) {
	sunComp = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("SunComp"));
	sunComp->SetStaticMesh(Cast<UStaticMesh>(sun));
	sunComp->bOwnerNoSee = false;
	sunComp->bCastDynamicShadow = false;
	sunComp->CastShadow = false;
	//sunComp->BodyInstance.SetObjectType(ECC_WorldDynamic);
	//sunComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	/*sunComp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
	sunComp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);
	sunComp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Block);
	sunComp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Block);*/
	sunComp->SetHiddenInGame(false);

	this->rotation = sunComp->GetComponentRotation();
	this->rotation.Yaw += rotationSpeed;
	this->sunComp->AttachParent = RootComponent;
}

void ASolarSystem::LoadAssets() {
	AssetManager::CreateObjectLibrary<UStaticMesh>(EMeshType::StaticMesh, FString(TEXT("/Game/UnrealGalaxies/Meshes/Planets")));
	this->sun = AssetManager::LoadAsset(AssetManager::GetObjectLibraries()[EMeshType::StaticMesh], FName(TEXT("Sun")));
	if (!sun) {
		UE_LOG(LogTemp, Log, TEXT("Shit"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Yay!"));
	}
}

void ASolarSystem::BeginPlay() {
	
}

void ASolarSystem::Tick(float deltaTime) {
	timeToTick -= deltaTime;
	if (timeToTick <= 0.f) {
		RotateSun();
		for (APlanet* p : planets) {
			p->Update();
		}
		timeToTick = gameSpeed;
	}
}

void ASolarSystem::RotateSun() {
	FTransform transform = sunComp->GetComponentTransform();
	transform.ConcatenateRotation(rotation.Quaternion());
	transform.NormalizeRotation();
	sunComp->SetWorldTransform(transform);
}

void ASolarSystem::CreatePlanets() {
	for (int32 i = 1; i < numPlanets + 1; i++) {
		APlanet* planet = (PlanetFactory::Create(this,i));
		planet->GetRootComponent()->AttachParent = RootComponent;
		planets.Add(planet);
	}

	FVector boundsExtend, boundsOrigin;
	GetActorBounds(false, boundsOrigin, boundsExtend);
	diameter = boundsExtend.X * numPlanets * 15;
}

void ASolarSystem::CreateCollisionSphere() {
	collisionSphere->SetSphereRadius(diameter, true);
	collisionSphere->OnComponentBeginOverlap.AddDynamic(this,&ASolarSystem::OnEnter);
	collisionSphere->OnComponentEndOverlap.AddDynamic(this, &ASolarSystem::OnLeave);
	this->SetActorHiddenInGame(true);
	sunComp->SetHiddenInGame(true);
	for (APlanet* p : planets) {
		p->SetActorHiddenInGame(true);
		p->GetRootComponent()->SetHiddenInGame(true, true);
	}
}

void ASolarSystem::OnEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor && (OtherActor != this) && Cast<APawn>(OtherActor) && OtherComp) {
		this->SetActorHiddenInGame(false);
		sunComp->SetHiddenInGame(false);
		for (APlanet* p : planets) {
			p->SetActorHiddenInGame(false);
			p->GetRootComponent()->SetHiddenInGame(false, true);
		}
	}
}

void ASolarSystem::OnLeave(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && (OtherActor != this) && Cast<APawn>(OtherActor) && OtherComp) {
		this->SetActorHiddenInGame(true);
		sunComp->SetHiddenInGame(true);
		for (APlanet* p : planets) {
			p->SetActorHiddenInGame(true);
			p->GetRootComponent()->SetHiddenInGame(true, true);
		}
	}
}





