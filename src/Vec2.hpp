#pragma once

#include <SFML\System\Vector2.hpp>

template <class T>
class Vec2 : public sf::Vector2<T>
{
public:
	Vec2() : sf::Vector2<T>() {}
	Vec2(T x, T y) : sf::Vector2<T>(x, y) {}
	Vec2(sf::Vector2<T> v) : sf::Vector2<T>(v.x, v.y) {}

	void Set(T x, T y);
	void Set(Vec2 v);

	T Length();
	T Dot(Vec2 v);
	Vec2<T> Normalise();
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<unsigned int> Vec2u;