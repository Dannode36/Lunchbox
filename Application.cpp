#include "Application.h"
#include <iostream>
#include <sstream>

Application::Application()
{
}

Application::~Application()
{
}

int Application::Start(int argResX, int argResY, float argViewSpeed)
{
    const int mapSize{ 64 };
    resX = argResX;
    resY = argResY;
    viewSpeed = argViewSpeed;

    sf::Time dt;
    sf::Time lastdt;

    sf::RenderWindow window(sf::VideoMode(resX, resY), "Lunchbox");
    window.setFramerateLimit(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui::SFML::Init(window);
    view.setSize(resX, resY);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    auto tileMap = LoadTileMap(mapSize);

    sf::RectangleShape tileSelector(sf::Vector2f(gridSize_f - tileMap[0][0].getOutlineThickness(), gridSize_f - tileMap[0][0].getOutlineThickness()));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    sf::Clock deltaClock;
    //MAIN LOOP
    while (window.isOpen()) {
        dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        mousePosScreenLast = mousePosScreen;
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
        UpdateEvents(window);

        //ImGui Windows

        //fps
        float fps = 1.f / dt.asSeconds();
        lastdt = dt;

        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

        ImGui::Begin("Colour");
        ImGui::Text(std::to_string(fps).c_str());
        if (ImGui::ColorEdit3("Colour", drawColourArray)) {
            drawColour.r = drawColourArray[0] * 255;
            drawColour.g = drawColourArray[1] * 255;
            drawColour.b = drawColourArray[2] * 255;
        }
        ImGui::Text(ss.str().c_str());
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ImGui::GetIO().WantCaptureMouse) {
            tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(drawColour);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !ImGui::GetIO().WantCaptureMouse) {
            view.move(-(mousePosScreen.x - mousePosScreenLast.x) * dragSpeedCoefficient, -(mousePosScreen.y - mousePosScreenLast.y) * dragSpeedCoefficient);
        }

        //Random stuff TODO
        Update();

        //RENDERING
        window.clear();

        //Draw Canvas
        window.setView(view);

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

        tileSelector.setPosition(mousePosGrid.x * gridSize_f, mousePosGrid.y * gridSize_f);
        window.draw(tileSelector);

        //Draw UI
        window.setView(window.getDefaultView());

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void Application::Update() {

}

void Application::UpdateEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta < 0) {
                view.zoom(2.f);
                dragSpeedCoefficient *= 2.f;
            }
            else if (event.mouseWheelScroll.delta > 0) {
                view.zoom(0.5f);
                dragSpeedCoefficient *= 0.5f;
            }
        }
    }
}


std::vector<std::vector<sf::RectangleShape>> Application::LoadTileMap(int mapSize) {

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
    return tileMap;
}

void Application::CalculateGridRenderBounds(int& fromX, int& toX, int& fromY, int& toY, int mapSize) {
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