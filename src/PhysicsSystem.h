#pragma once
#include "System.h"


class PhysicsSystem : public System {
public:
	const double GRAVITY = -9.8;
	const double SIMSPEED = 1;
	void Init();

	void Update(float dt);
};
