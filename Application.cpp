#include "Application.h"
#include <iostream>
#include <sstream>
#include "DrawingTools.h"
#include "CustomUtil.h"
#include "IO.h"

Application::Application()
{
}

Application::~Application()
{
}

int Application::Start(const int argResX, const int argResY, const int mSizeX, const int mSizeY, const float argViewSpeed)
{
    resX = argResX;
    resY = argResY;
    this->mapSizeX = mSizeX;
    this->mapSizeY = mSizeY;
    viewSpeed = argViewSpeed;

    sf::Time dt;
    sf::Time lastdt;

    sf::RenderWindow window(sf::VideoMode(resX, resY), "Lunchbox");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

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

    //canvas.LoadCanvas(grid, mapSizeX, gridSize_f);

    grid = LoadImage(*this, "image2.png", gridSize_f);
    canvas.LoadCanvasLines(gridLines, mapSizeX, gridSize_f);
    std::cout << mapSizeX;
    sf::RectangleShape tileSelector(sf::Vector2f(gridSize_f, gridSize_f));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    sf::Clock deltaClock;
    //MAIN LOOP
    while (window.isOpen()) {
        dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        //Mouse pos calcs
        mousePosScreenLast = mousePosScreen;
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0.f) {
            mousePosGrid.x = (mousePosView.x / gridSize_u);
        }
        else
        {
            mousePosGrid.x = 0;
        }
        if (mousePosView.y >= 0.f) {
            mousePosGrid.y = (mousePosView.y / gridSize_u);
        }
        else
        {
            mousePosGrid.y = 0;
        }

        //Do events like input
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
        if (ImGui::ColorEdit4("Colour", drawColourArray)) {
            drawColour.r = drawColourArray[0] * 255;
            drawColour.g = drawColourArray[1] * 255;
            drawColour.b = drawColourArray[2] * 255;
            drawColour.a = drawColourArray[3] * 255;
        }
        ImGui::Text(ss.str().c_str());
        ImGui::End();

        ImGui::Begin("DockTest");
        ImGui::Text("Test Window");
        ImGui::Checkbox("Show Grid", &drawGrid);
        ImGui::End();

        //Input per frame (should be done in events but oh well)
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !ImGui::GetIO().WantCaptureMouse) {
            view.move(-(mousePosScreen.x - mousePosScreenLast.x) * dragSpeedCoefficient, -(mousePosScreen.y - mousePosScreenLast.y) * dragSpeedCoefficient);
        }

        //Random stuff TODO
        Update();

        //RENDERING
        window.clear(sf::Color(10, 10, 10, 0));

        //Draw Canvas
        window.setView(view);
        window.draw(grid);
        if (drawGrid) {
            window.draw(gridLines);
        }

        tileSelector.setSize(sf::Vector2f(gridSize_f, gridSize_f));
        //tileSelector.setOutlineThickness(tileMap[1][1].getOutlineThickness());
        tileSelector.setPosition(clip(mousePosGrid.x * gridSize_f, 0, mapSizeX * gridSize_f - gridSize_f), clip(mousePosGrid.y * gridSize_f, 0, mapSizeX * gridSize_f - gridSize_f));
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
    //Funky stuff
}

sf::Vector2u lineStartPos;
sf::Vector2u linePrevPos;

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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    drawState = PEN;
                    canvas.DrawPen(grid, mousePosGrid, mapSizeX, drawColour);
                    canvas.DialatePoint(grid, sf::Vector2i(mousePosGrid), mapSizeX);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    lineStartPos = mousePosGrid;
                    linePrevPos = mousePosGrid;
                    drawState = LINE;
                }
            }
            //Do Drawing
            else if ((event.type == sf::Event::MouseMoved)) {
                if (drawState == PEN) {
                    canvas.DrawPen(grid, mousePosGrid, mapSizeX, drawColour);
                    canvas.DialatePoint(grid, sf::Vector2i(mousePosGrid), mapSizeX);
                }
                else if (drawState == LINE) {
                    canvas.DrawLine(grid, sf::Vector2i(lineStartPos), sf::Vector2i(mousePosGrid), sf::Vector2i(linePrevPos), mapSizeX, drawColour);
                    linePrevPos = mousePosGrid;
                }
                else if (drawState == COLORPICK) {
                    drawColour = windowTex.copyToImage().getPixel(mousePosWindow.x, mousePosWindow.y);
                }
            } 

            //Cancel Drawing
            else if (event.type == sf::Event::MouseButtonReleased) {
                drawState = STOP;
            }
        }
        else {
            drawState = STOP;
        }

        if (!ImGui::GetIO().WantCaptureKeyboard) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S && event.key.control) {
                    std::cout << SaveImage("image", grid, mapSizeX, mapSizeX) << "\n";
                }
            }
        }
    }
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