#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Math
{
public:
	void projectRect(float projections[4], sf::FloatRect rect, sf::Vector2f projVect)
	{
		std::vector<sf::Vector2f> corners;
		corners.push_back(sf::Vector2f(rect.left, bBounds.top));
		corners.push_back(sf::Vector2f(rect.left + bBounds.width, bBounds.top));
		corners.push_back(sf::Vector2f(bBounds.left, bBounds.top + bBounds.height));
		corners.push_back(sf::Vector2f(bBounds.left + bBounds.width, bBounds.top + bBounds.height));

		for each (sf::Vector2f corner in corners)
		{
			
		}
	}
};