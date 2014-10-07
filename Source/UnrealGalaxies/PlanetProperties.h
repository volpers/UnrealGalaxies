#pragma once

#include "UnrealGalaxies.h"

namespace EPlanet {
	enum Type {
		DEFAULT, EARTHEN, DESERT, VULCANIC, ICE, GAS, DEAD, MOON, TYPE_MAX = MOON
	};
}

class PlanetProperties {
	public:
	PlanetProperties() : size(0), number(0), speed(0), orbitSpeed(0), type(EPlanet::DEFAULT) {};
	PlanetProperties(float _size, int32 _number, EPlanet::Type _type) : size(_size), number(_number), type(_type) {};
	~PlanetProperties();
	float size;
	float speed;
	float orbitSpeed;
	int32 number;
	EPlanet::Type type;
};

 