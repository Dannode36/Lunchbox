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

void CalculateGridRenderBounds(int& fromX, int& toX, int& fromY, int& toY, int mapSize) {
    if (fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize;

    if (toX < 0)
        toX = 0;
    else if (toX >= mapSize)
        toX = mapSize;

    if (fromY < 0)
        fromY = 0;
    else if (fromY >= mapSize)
        fromY = mapSize;

    if (toY < 0)
        toY = 0;
    else if (toY >= mapSize)
        toY = mapSize;
}
bool IsMouseOwnedImGui(ImGuiIO& io) {
    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDownOwned); i++) {
        if (io.MouseDownOwned[i] == true) {
            return true;
        }
    }
    return false;
}