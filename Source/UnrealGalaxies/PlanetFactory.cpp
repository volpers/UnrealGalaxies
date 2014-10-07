#include "UnrealGalaxies.h"
#include "Logger.h"
#include "PlanetFactory.h"



PlanetFactory::PlanetFactory() {
}


PlanetFactory::~PlanetFactory() {
}


APlanet* PlanetFactory::Create(AActor* parent, int32 number) {
	UWorld* world = parent->GetWorld();
	if(world) {
		APlanet* planet = world->SpawnActor<APlanet>(APlanet::StaticClass());
		FVector boundsOrigin, boundsExtends, location;
		float size = FMath::FRandRange(0.1f, 2.f);
		float speed = FMath::FRandRange(0.05f, 0.4f);
		EPlanet::Type type = static_cast<EPlanet::Type>(FMath::RandRange(0,(int) EPlanet::TYPE_MAX-1));
		planet->GetRootComponent()->AttachParent = parent->GetRootComponent();
		parent->GetActorBounds(false, boundsOrigin, boundsExtends);
		location = FVector(parent->GetActorLocation().X + (number * boundsExtends.X * 2), parent->GetActorLocation().Y + (number * boundsExtends.Y * 2), parent->GetActorLocation().Z);
		planet->SetProperties(parent->GetActorLocation(), size, number, speed, type);
		planet->SetActorLocation(location);
		return planet;
	}
	return NULL;
}

APlanet* PlanetFactory::CreateSpecific(AActor* parent, EPlanet::Type type) {
	UWorld* world = parent->GetWorld();
	if (world) {
		APlanet* planet = world->SpawnActor<APlanet>(APlanet::StaticClass());
		FVector boundsOrigin, boundsExtends, location;
		parent->GetActorBounds(false, boundsOrigin, boundsExtends);
		float size = boundsExtends.X / 2.f;
		float speed = FMath::FRandRange(0.05f, 0.4f);
		location = FVector(parent->GetActorLocation().X + boundsExtends.X * 2, parent->GetActorLocation().Y + boundsExtends.Y * 2, parent->GetActorLocation().Z);
		//planet->GetRootComponent()->AttachParent = parent->GetRootComponent();
		planet->SetProperties(parent->GetActorLocation(), size, 1, speed, type);
		planet->SetActorLocation(location);
		return planet;
	}
	return NULL;
}

//array<float> PlanetFactory::UniqueRandomF(int32 length, float from, float to) {
//	array<float, length> range;
//	if (from < to) {
//		float step = (to - from) / length;
//		for (int32 i = 1; i < length + 1; i++) {
//			range[i-1] = step * i;
//		}
//		random_shuffle(range.begin(), range.end());
//		return range;
//	}
//	return NULL;
//}
//
//array<int32> PlanetFactory::UniqueRandomI(int from, int to) {
//	if (from < to) {
//		int32 length = to - from;
//		array<int32, length> range;
//		for (int32 i = 0; i < length; i++) {
//			range[i] = from + i;
//		}
//		random_shuffle(range.begin(), range.end());
//		return range;
//	}
//	return NULL;
//}
