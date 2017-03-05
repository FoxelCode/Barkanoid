#include "Game/Entities/GameArea.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "Collision/ListCollider.hpp"

GameArea::GameArea(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(pos), size(size), wallThickness(16.0f)
{
	leftWall = new Wall(sf::Vector2f(0.0f, wallThickness + pos.y), sf::Vector2f(wallThickness, size.y));
	topWall = new Wall(sf::Vector2f(0.0f, pos.y), sf::Vector2f(size.x, wallThickness));
	rightWall = new Wall(sf::Vector2f(size.x - wallThickness, wallThickness + pos.y), sf::Vector2f(wallThickness, size.y));

	ListCollider* col = new ListCollider(this);
	col->AddCollider(leftWall->GetCollider());
	col->AddCollider(topWall->GetCollider());
	col->AddCollider(rightWall->GetCollider());
	collider = col;
}

GameArea::~GameArea()
{
	delete leftWall;
	delete topWall;
	delete rightWall;
}

void GameArea::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*leftWall, states);
	target.draw(*topWall, states);
	target.draw(*rightWall, states);
}
