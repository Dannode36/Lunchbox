#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Overlord.h"
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include "Game.h"
#include <iostream>

Overlord gOverlord;

int resX = 1920;
int resY = 1080;

float gridSize_f = 100.f;
unsigned gridSize_u = static_cast<unsigned>(gridSize_f);

float viewSpeed = 200.f;

int fromX{};
int fromY{};
int toX{};
int toY{};

float drawColourArray[3];
sf::Color drawColour;

bool draw{ true };

int main() {

    sf::Time dt;
    sf::Time lastdt;
    gOverlord.Init();

    sf::RenderWindow window(sf::VideoMode(resX, resY), "Lunchbox");
    window.setFramerateLimit(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.MouseDownOwned


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

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
        return ENOENT;
    }
    sf::Text text;
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    //Init Game Elements
    sf::RectangleShape shape(sf::Vector2f(gridSize_f, gridSize_f));

    const int mapSize = 64;

    std::vector<std::vector<sf::RectangleShape>> tileMap;

    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for (int x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize, sf::RectangleShape());
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSize_f, gridSize_f));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(2.f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSize_f, y * gridSize_f);
        }
    }

    sf::RectangleShape tileSelector(sf::Vector2f(gridSize_f - tileMap[0][0].getOutlineThickness(), gridSize_f - tileMap[0][0].getOutlineThickness()));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        ImGui::SFML::Update(window, dt);
        dt = deltaClock.restart();

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
        //Events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta < 0) {
                    view.zoom(1.1f);
                    printf("zoomed in");
                }
                else if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(0.9f);
                }
                //view.zoom(event.mouseWheelScroll.delta + 0.1f);
                std::cout<< event.mouseWheelScroll.delta << "\n";
            }
            if (io.WantCaptureMouse) {
                draw = false;
            }
            else {
                draw = true;
            }
        }

        float fps = 1.f / dt.asSeconds();
        lastdt = dt;

        //ImGui Window Logic
        //ImGui::SFML::Update(window, dt);

        ImGui::Begin("Colour");

        ImGui::Button(std::to_string(fps).c_str());

        if (ImGui::ColorPicker3("Colour", drawColourArray)) {
            drawColour.r = drawColourArray[0] * 255;
            drawColour.g = drawColourArray[1] * 255;
            drawColour.b = drawColourArray[2] * 255;
            std::cout << drawColourArray[0] << "\n";
        }
        ImGui::End();


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

        

        //Drawing Input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(drawColour);
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::White);
            }
        }

        //Update game objects

        tileSelector.setPosition(mousePosGrid.x * gridSize_f, mousePosGrid.y * gridSize_f);

        window.clear();

        //Draw Canvas;
        window.setView(view);
        window.draw(shape);

        fromX = view.getCenter().x / gridSize_f - ((view.getSize().x / 2) / gridSize_u) - 1;
        toX = view.getCenter().x / gridSize_f + ((view.getSize().x / 2) / gridSize_u) + 1;
        fromY = view.getCenter().y / gridSize_f - ((view.getSize().y / 2) / gridSize_u) - 1;
        toY = view.getCenter().y / gridSize_f + ((view.getSize().y / 2) / gridSize_u) + 1;
        CalculateGridRenderBounds(fromX, toX, fromY, toY, mapSize);

        for (int x = fromX; x < toX; x++)
        {
            for (int y = fromY; y < toY; y++)
            {
                window.draw(tileMap[x][y]);
            }
        }

        /*for (int x = 0; x < mapSize; x++)
        {
            for (int y = 0; y < mapSize; y++)
            {
                window.draw(tileMap[x][y]);
            }
        }*/

        window.draw(tileSelector);

        //Draw UI
        window.setView(window.getDefaultView());

        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
        text.setString(ss.str());

        window.draw(text);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
