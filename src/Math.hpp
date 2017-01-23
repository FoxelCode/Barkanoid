#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Math
{
public:
	static void projectRect(float projections[4], sf::FloatRect rect, sf::Vector2f projVect)
	{
		std::vector<sf::Vector2f> corners;
		corners.push_back(sf::Vector2f(rect.left, rect.top));
		corners.push_back(sf::Vector2f(rect.left + rect.width, rect.top));
		corners.push_back(sf::Vector2f(rect.left, rect.top + rect.height));
		corners.push_back(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));

		for (int i = 0; i < 4; i++)
		{
			float proj = dot(corners[i], projVect);
			projections[i] = proj;
		}
	}

	static float dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static sf::Vector2f normalise(sf::Vector2f a)
	{
		return a / magnitude(a);
	}

	static float magnitude(sf::Vector2f a)
	{
		return sqrtf(a.x * a.x + a.y * a.y);
	}

	static sf::FloatRect makeRelativeTo(sf::FloatRect a, sf::Vector2f point)
	{
		return sf::FloatRect(a.left - point.x, a.top - point.y, a.width, a.height);
	}
};