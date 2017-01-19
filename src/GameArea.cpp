#include "GameArea.hpp"
#include <SFML\Graphics\RenderTarget.hpp>

GameArea::GameArea(sf::Vector2f pos, sf::Vector2f size)
	: pos(pos), size(size)
{
	leftWall = new sf::RectangleShape(sf::Vector2f(wallThickness, size.y));
	leftWall->setPosition(pos);
	topWall = new sf::RectangleShape(sf::Vector2f(size.x, wallThickness));
	topWall->setPosition(pos);
	rightWall = new sf::RectangleShape(sf::Vector2f(wallThickness, size.y));
	rightWall->setPosition(sf::Vector2f(pos.x + size.x - wallThickness, 0.0f));
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
