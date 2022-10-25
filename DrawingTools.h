#pragma once
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include "CustomUtil.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class DrawTool
{
public:
	DrawTool();
	~DrawTool();
	void Draw();
private:

};

void EFLALine(TileMap& tileMap, float x1, float y1, float x2, float y2, const sf::Color& color);
void BresenhamLine(TileMap& tileMap, int x1, int y1, int x2, int y2, const sf::Color& color);
void BresenhamLineUndo(TileMap& tileMap, int x1, int y1, int x2, int y2);
//void GradientLine(float x1, float y1, float x2, float y2, TileMap tileMap, const sf::Color& color1, const sf::Color& color2);
