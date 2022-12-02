#include "CustomUtil.h"

int clip(const int& n, const int& lower, const int& upper)
{
	return n <= lower ? lower : n >= upper ? upper : n;
}

sf::Vector2i clip(sf::Vector2i n, sf::Vector2i lower, sf::Vector2i upper)
{
	return sf::Vector2i(clip(n.x, lower.x, upper.x), clip(n.y, lower.y, upper.y));
}
