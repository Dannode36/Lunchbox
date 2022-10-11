#pragma once
#include "Types.h"
#include <cstdint>

struct Renderer {

	bool active;
};

struct Transform {
	Vec2 position;
	double rotation;
	Vec2 scale;
};

struct RigidBody
{
	//bool sleeping;
	Vec2 gravity;
	Vec2 velocity;
	bool debug;
	//TODO
};
