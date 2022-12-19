#pragma once
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include "CustomUtil.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class Canvas
{
public:
	Canvas();
	~Canvas();
	void LoadCanvas(sf::VertexArray& vertArr, const int mapSize, const int gridSize);
	void LoadCanvasLines(sf::VertexArray& lineArr, const int mapSize, const int gridSize);
	void DrawPen(sf::VertexArray& vertArr, const sf::Vector2u point, const int mapSize, const sf::Color& color);
	void DrawLine(sf::VertexArray& vertArr, sf::Vector2i start, sf::Vector2i end, sf::Vector2i prev, const int mapSize, const sf::Color& color);
	void DialatePoint(sf::VertexArray& vertArr, sf::Vector2i point, const int mapSize);
	//void DrawGradientLine(float x1, float y1, float x2, float y2, TileMap tileMap, const sf::Color& color1, const sf::Color& color2);
private:
	void ClearPrevLine(sf::VertexArray& vertArr, sf::Vector2i start, sf::Vector2i prev, const int mapSize);
};

enum DrawingState
{
	STOP,
	PEN,
	LINE,
	COLORPICK
};
