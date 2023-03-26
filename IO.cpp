#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "IO.h"

std::string SaveImage(const std::string& filename, const sf::VertexArray& map, const int mapSizeY, const int mapSizeX) {
	sf::Image exportImage;
	exportImage.create(mapSizeX, mapSizeY);

	for (size_t x = 0; x < mapSizeX; x++)
	{
		for (size_t y = 0; y < mapSizeY; y++)
		{
			exportImage.setPixel(x, y, map[(x * mapSizeX * 4) + (y * 4)].color);
		}
	}

	if (exportImage.saveToFile(filename + ".png")) {
		return filename + ".png";
	}
	else {
		return "null";
	}
}

sf::VertexArray LoadImage(Application& app, const std::string& filename, const int gridSize) {
	sf::Image importImage;
	if (!importImage.loadFromFile(filename)) {
		assert(false);
	}
	const int mapSizeX = importImage.getSize().x;
	const int mapSizeY = importImage.getSize().y;

	sf::VertexArray map;
	map.clear();
	map.setPrimitiveType(sf::Quads);
	map.resize(mapSizeX * mapSizeY * 4);

	int i = 0;
	for (int x = 0; x < mapSizeX; x++)
	{
		for (int y = 0; y < mapSizeY; y++)
		{
			map[i + 0].position = sf::Vector2f(x * gridSize, y * gridSize);
			map[i + 1].position = sf::Vector2f(x * gridSize, y * gridSize + gridSize);
			map[i + 2].position = sf::Vector2f(x * gridSize + gridSize, y * gridSize + gridSize);
			map[i + 3].position = sf::Vector2f(x * gridSize + gridSize, y * gridSize);

			map[i + 0].color = importImage.getPixel(x, y);
			map[i + 1].color = importImage.getPixel(x, y);
			map[i + 2].color = importImage.getPixel(x, y);
			map[i + 3].color = importImage.getPixel(x, y);

			i += 4;
		}
	}
	app.mapSizeX = mapSizeX;
	app.mapSizeY = mapSizeY;
	return map;
}
