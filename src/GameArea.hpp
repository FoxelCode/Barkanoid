#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

class GameArea : public sf::Drawable
{
public:
	GameArea(sf::Vector2f pos, sf::Vector2f size);
	~GameArea();

	sf::RectangleShape* leftWall = nullptr;
	sf::RectangleShape* topWall = nullptr;
	sf::RectangleShape* rightWall = nullptr;

	sf::Vector2f pos;
	sf::Vector2f size;

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	float wallThickness;
};