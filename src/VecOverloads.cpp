#include "Types.h"

Vec2 operator+(Vec2 a, Vec2 b) {
	Vec2 sum{ a.x + b.x, a.y + b.y };
	return sum;
}
Vec2 operator-(Vec2 a, Vec2 b) {
	Vec2 diff{ a.x - b.x, a.y - b.y };
	return diff;
}
Vec2 operator-(Vec2 a) {
	Vec2 flip{ -a.x, -a.y };
	return flip;
}
Vec2 operator*(Vec2 a, Vec2 b) {
	Vec2 prod{ a.x * b.x, a.y * b.y };
	return prod;
}
Vec2 operator*(Vec2 a, double b) {
	Vec2 prod{ a.x * b, a.y * b };
	return prod;
}
Vec2 operator/(Vec2 a, Vec2 b) {
	Vec2 quot{ a.x / b.x, a.y / b.y };
	return quot;
}