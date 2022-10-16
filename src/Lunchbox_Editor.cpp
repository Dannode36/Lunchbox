#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Overlord.h"

Overlord gOverlord;

int resX = 1920;
int resY = 1080;

float gridSize_f = 100.f;
unsigned gridSize_u = static_cast<unsigned>(gridSize_f);

int main() {

    gOverlord.Init();

    sf::RenderWindow window(sf::VideoMode(resX, resY), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::View view;
    view.setSize(resX, resY);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    //Init Game Elements
    sf::RectangleShape shape(sf::Vector2f(gridSize_f, gridSize_f));


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.setView(view);
        //Draw Game;
        //shape.setPosition(window.getDefaultView().getCenter().x - shape.getRadius(), window.getDefaultView().getCenter().y - shape.getRadius());
        window.draw(shape);

        window.setView(window.getDefaultView());
        //Draw UI

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}