#include <SFML/Graphics/VertexArray.hpp>
#include <string>
#include "Application.h"

std::string SaveImage(const std::string& filename, const sf::VertexArray& map, const int mapSizeY, const int mapSizeX);
sf::VertexArray LoadImage(Application& app, const std::string& filename, const int gridSize);
