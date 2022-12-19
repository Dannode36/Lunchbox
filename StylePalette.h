#pragma once
#include <vector>
#include <SFML/Graphics/Color.hpp>


class StylePalette
{
public:
	StylePalette();
	~StylePalette();
	std::vector<sf::Color> colours{};
private:
};

extern std::vector<StylePalette> palettes;
