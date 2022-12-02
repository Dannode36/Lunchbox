#pragma once
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

using TileMap = std::vector<std::vector<sf::RectangleShape>>;

int clip(const int& n, const int& lower, const int& upper);
sf::Vector2i clip(sf::Vector2i n, sf::Vector2i lower, sf::Vector2i upper);
