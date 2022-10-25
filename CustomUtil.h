#pragma once
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

using TileMap = std::vector<std::vector<sf::RectangleShape>>;

template <typename T>
T clip(const T& n, const T& lower, const T& upper);
int clip(const int& n, const int& lower, const int& upper);