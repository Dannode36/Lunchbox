#pragma once
#include <bitset>
#include <vector>
#include <functional>

using Entity = uint16_t;
const Entity MAX_ENTITIES = 256;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

enum CreatureState
{
	UNACTIVE,
	DEAD,
	PASSIVE,
	ANGERED,
	SCARED
};

struct Vec2
{
	float x{};
	float y{};
	Vec2 operator+=(Vec2 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
};
Vec2 operator+(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a);
Vec2 operator*(Vec2 a, Vec2 b);
Vec2 operator*(Vec2 a, double b);
Vec2 operator/(Vec2 a, Vec2 b);
