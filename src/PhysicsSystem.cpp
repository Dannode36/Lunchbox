#include "PhysicsSystem.h"
#include "Overlord.h"
#include "Components.h"
#include <iostream>
#include <vector>


extern Overlord gOverlord;

void PhysicsSystem::Init() {

}

void PhysicsSystem::Update(float dt) {

	for (auto const& entity : mEntities)
	{
		auto& rigidBody = gOverlord.GetComponent<RigidBody>(entity);
		auto& transform = gOverlord.GetComponent<Transform>(entity);
		rigidBody.velocity.y += GRAVITY * dt * SIMSPEED;
		transform.position += rigidBody.velocity * dt * SIMSPEED;

		if (transform.position.y < 0) {
			transform.position.y = 0;
			rigidBody.velocity.y = -rigidBody.velocity.y - 1;
		}

		if (rigidBody.debug) {
			std::cout << "X:" << transform.position.y << " Current Y-Velocity: " << rigidBody.velocity.y <<"\n";
		}
	}
}
