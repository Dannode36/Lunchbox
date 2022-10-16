#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Overlord.h"
#include <SFML/Graphics/Text.hpp>
#include <sstream>

Overlord gOverlord;

int resX = 1920;
int resY = 1080;

float gridSize_f = 100.f;
unsigned gridSize_u = static_cast<unsigned>(gridSize_f);

float viewSpeed = 200.f;


int main() {
    sf::Time dt;
    sf::Time lastdt;
    gOverlord.Init();

    sf::RenderWindow window(sf::VideoMode(resX, resY), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::View view;
    view.setSize(resX, resY);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    sf::Font font;
    if (!font.loadFromFile("src/fonts/Akira-Expanded.otf")) {
        return 1;
    }
    sf::Text text;
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    //Init Game Elements
    sf::RectangleShape shape(sf::Vector2f(gridSize_f, gridSize_f));

    sf::Clock deltaClock;
    while (window.isOpen()) {
        dt = deltaClock.restart();

        //Events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float fps = 1.f / dt.asSeconds();
        lastdt = dt;

        ImGui::SFML::Update(window, dt);

        ImGui::Begin("window");
        ImGui::Button(std::to_string(fps).c_str());
        ImGui::End();

        //Update Input

        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0.f) {
            mousePosGrid.x = (mousePosView.x / gridSize_u);
        }
        if (mousePosView.y >= 0.f) {
            mousePosGrid.y = (mousePosView.y / gridSize_u);
        }

        std::stringstream ss;

        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

        text.setString(ss.str());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //Up
            view.move(0.f, -viewSpeed * dt.asSeconds());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //Down
            view.move(0.f, viewSpeed * dt.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //Left
            view.move(-viewSpeed * dt.asSeconds(), 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //Right
            view.move(viewSpeed * dt.asSeconds(), 0.f);
        }

        window.clear();
        window.setView(view);
        //Draw Game;
        //shape.setPosition(window.getDefaultView().getCenter().x - shape.getRadius(), window.getDefaultView().getCenter().y - shape.getRadius());
        window.draw(shape);

        window.setView(window.getDefaultView());
        //Draw UI

        ImGui::SFML::Render(window);
        window.draw(text);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
