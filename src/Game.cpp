#include <stdio.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include "Overlord.h"
#include "PhysicsSystem.h"
#include "DialogSystem.h"
#include <chrono>
#include "Game.h"

Application::Application()
{
}

Application::~Application()
{
}
void Application::Init() {

}

void Application::InitECS() {
	/*gOverlord.Init();
    gOverlord.RegisterComponent<Transform>();
    gOverlord.RegisterComponent<RigidBody>();
    Signature signature;
    auto physicsSystem = gOverlord.RegisterSystem<PhysicsSystem>();
    signature.set(gOverlord.GetComponentType<Transform>());
    signature.set(gOverlord.GetComponentType<RigidBody>());
    gOverlord.SetSystemSignature<PhysicsSystem>(signature);

    std::vector<Entity> entities(MAX_ENTITIES);
    float incr = 0;
    for (auto& entity : entities)
    {
        entity = gOverlord.CreateEntity();

        gOverlord.AddComponent(
            entity,
            RigidBody{
                Vec2{0, -9.8},
                Vec2{0, 0},
                false
            });

        gOverlord.AddComponent(
            entity,
            Transform{
                Vec2{0, 10 + incr}
            });
        incr += 0.01f;
    }
    float dt = 0.0f;*/
}