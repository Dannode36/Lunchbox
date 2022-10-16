#pragma once
#include "System.h"

class PhysicsSystem : public System {
public:
	const float GRAVITY = -9.8f;
	const float SIMSPEED = 1.0f;
	void Init();

	void Update(float dt);
};
