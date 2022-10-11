#pragma once
#include <bitset>
using Entity = uint16_t;
const Entity MAX_ENTITIES = 2;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Vec2
{
	double x{};
	double y{};
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