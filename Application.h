#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include "imgui_internal.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "DrawingTools.h"

class Application
{
public:
	int resX{};
	int resY{};

	const int mapSize{ 32 };
	float viewSpeed{};

	double dragSpeedCoefficient{1};

	float drawColourArray[3]{0};
	sf::Color drawColour{};

	int fromX{};
	int fromY{};
	int toX{};
	int toY{};

	std::string lastError{};

	sf::View view{};

	TileMap tileMap;

	Application();
	~Application();

	void Update();
	void UpdateEvents(sf::RenderWindow& window);
	int Start(int resX, int resY, float viewSpeed);

	TileMap LoadTileMap(int mapSize);
	void Draw(int x, int y, sf::Color& colour);
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
