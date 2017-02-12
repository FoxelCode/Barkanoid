#include "GameArea.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

GameArea::GameArea(sf::Vector2f pos, sf::Vector2f size)
	: pos(pos), size(size), wallThickness(20.0f)
{
	leftWall = new Wall(sf::Vector2f(0.0f, wallThickness), sf::Vector2f(wallThickness, size.y));
	topWall = new Wall(sf::Vector2f(), sf::Vector2f(size.x, wallThickness));
	rightWall = new Wall(sf::Vector2f(size.x - wallThickness, wallThickness), sf::Vector2f(wallThickness, size.y));
}

GameArea::~GameArea()
{
	delete leftWall;
	delete topWall;
	delete rightWall;
}

void GameArea::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*leftWall, states);
	target.draw(*topWall, states);
	target.draw(*rightWall, states);
}
