#include "Application.h"
#include <iostream>
#include <sstream>
#include "DrawingTools.h"
#include "CustomUtil.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Draw(int x, int y, sf::Color& colour) {

    if (x < mapSize && y < mapSize) {
        tileMap[x][y].setFillColor(drawColour);
    }
    else
    {
        std::string error{ "ERROR: Tried to draw out of vector bounds" };
        if (lastError != error) {
            std::cout << error << "\n";
            lastError = error;
        }
    }
}

int Application::Start(int argResX, int argResY, float argViewSpeed)
{
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
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //// Update and Render additional Platform Windows
    //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    //{
    //    ImGui::UpdatePlatformWindows();
    //    ImGui::RenderPlatformWindowsDefault();
    //}

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui::SFML::Init(window);
    view.setSize(resX, resY);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    tileMap = LoadTileMap(mapSize);

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

        ImGui::Begin("DockTest");
        ImGui::Text("Test Window");
        ImGui::End();

        //Keyboard & mouse
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
            Draw(mousePosGrid.x, mousePosGrid.y, drawColour);
        }
        /*else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

        }*/
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !ImGui::GetIO().WantCaptureMouse) {
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
                float t = view.getSize().x / window.getDefaultView().getSize().x;
                tileMap[x][y].setOutlineThickness(t);

                window.draw(tileMap[x][y]);
            }
        }

        tileSelector.setSize(sf::Vector2f(gridSize_f, gridSize_f));
        tileSelector.setOutlineThickness(tileMap[1][1].getOutlineThickness());
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

bool drawing{ false };
sf::Vector2u startPos;
sf::Vector2u prevPos;

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
                view.zoom(1.1f);
                dragSpeedCoefficient *= 1.1f;
            }
            else if (event.mouseWheelScroll.delta > 0) {
                view.zoom(0.9f);
                dragSpeedCoefficient *= 0.9f;
            }
        }

        if (!ImGui::GetIO().WantCaptureMouse) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    startPos = mousePosGrid;
                    drawing = true;
                }
            }
            else if ((event.type == sf::Event::MouseMoved) && drawing) {
                BresenhamLineUndo(tileMap, startPos.x, startPos.y, clip<int>(prevPos.x, 0, mapSize - 1), clip<int>(prevPos.y, 0, mapSize - 1));
                BresenhamLine(tileMap, startPos.x, startPos.y, clip<int>(mousePosGrid.x, 0, mapSize - 1), clip<int>(mousePosGrid.y, 0, mapSize - 1), drawColour);
                prevPos = mousePosGrid;
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    drawing = false;
                }
            }
        }
    }
}

TileMap Application::LoadTileMap(int mapSize) {

    TileMap tileMap;

    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for (int x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize, sf::RectangleShape());
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSize_f, gridSize_f));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(4.f);
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