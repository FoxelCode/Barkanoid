#pragma once

#include <SFML\Graphics\Drawable.hpp>

#include "Wall.hpp"

class GameArea : public GameObject
{
public:
	GameArea(sf::Vector2f pos, sf::Vector2f size);
	~GameArea();

	float GetWallThickness() { return wallThickness; }

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	Wall* leftWall = nullptr;
	Wall* topWall = nullptr;
	Wall* rightWall = nullptr;

	sf::Vector2f size;
	float wallThickness;
};