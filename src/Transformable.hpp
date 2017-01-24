#pragma once

#include "Vec2.hpp"

class Transformable
{
public:
	Transformable() : position() {}
	Transformable(Vec2f pos) : position(pos) {}

	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetPosition(Vec2f p) { position = p; }
	void Move(float x, float y) { position.x += x; position.y += y; }
	void Move(Vec2f v) { position += v; }

private:
	Vec2f position;
};