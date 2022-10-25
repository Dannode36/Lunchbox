#pragma once
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

using TileMap = std::vector<std::vector<sf::RectangleShape>>;

void EFLALine(TileMap& tileMap, float x1, float y1, float x2, float y2, const sf::Color& color);
void BresenhamLine(TileMap& tileMap, int x1, int y1, int x2, int y2, const sf::Color& color);
void BresenhamLineUndo(TileMap& tileMap, int x1, int y1, int x2, int y2);
//void GradientLine(float x1, float y1, float x2, float y2, TileMap tileMap, const sf::Color& color1, const sf::Color& color2);
