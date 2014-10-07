#pragma once

#include "PlanetProperties.h"
#include "Planet.h"
#include "Logger.h"
#include <string>
#include <array>
#include <algorithm>

using namespace std;

class PlanetFactory {
	public:
	PlanetFactory();
	~PlanetFactory();
	static APlanet* Create(AActor* parent, int32 number);
	static APlanet* CreateSpecific(AActor* parent, EPlanet::Type type);
};

