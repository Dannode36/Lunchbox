#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include "imgui_internal.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "DrawingTools.h"
#include <SFML/Graphics/Texture.hpp>

class Application
{
public:
	int resX{};
	int resY{};
	int mapSizeX;
	int mapSizeY;

	bool drawGrid{ true };
	float viewSpeed{};

	double dragSpeedCoefficient{ 1 };

	float drawColourArray[4]{ 0 };
	sf::Color drawColour{};

	sf::View view{};

	DrawingState drawState = STOP;
	sf::Texture windowTex;
	Canvas canvas{};
	sf::VertexArray grid;
	sf::VertexArray gridLines;

	Application();
	~Application();

	void Update();
	void UpdateEvents(sf::RenderWindow& window);
	int Start(const int resX, const int resY, const int mapSizeX, const int mapSizeY,const float viewSpeed);

private:
	void CalculateGridRenderBounds(int& fromX, int& toX, int& fromY, int& toY, int mapSize);

	float gridSize_f{ 100.f };
	unsigned gridSize_u{ static_cast<unsigned>(gridSize_f) };

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosScreenLast;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
};
