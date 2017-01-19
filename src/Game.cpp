#include "Game.hpp"
#include <vector>
#include <cfloat>
#include <iostream>
#include <SFML\Window\Mouse.hpp>

Game::Game(sf::RenderWindow& window, sf::Vector2u size)
	: window(&window), size(size)
{
	ball = new Ball(sf::Vector2f(100.0f, 100.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 100.0f));
	gameArea = new GameArea(sf::Vector2f(), sf::Vector2f((float)size.x, (float)size.y));
}

void Game::Update(float delta)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	paddle->setPosition((float)mousePos.x, paddle->getPosition().y);

	ball->Update(delta);
	Collide(ball, paddle);
	Collide(ball, gameArea->leftWall);
	Collide(ball, gameArea->topWall);
	Collide(ball, gameArea->rightWall);
}

void Game::Collide(Ball* a, sf::RectangleShape* b)
{
	sf::FloatRect bBounds = b->getGlobalBounds();
	sf::Vector2f aPos = a->getPosition();
	sf::Vector2f aCenter = sf::Vector2f(aPos.x + a->getRadius(), aPos.y + a->getRadius());
	sf::Vector2f bCenter = sf::Vector2f(bBounds.left + bBounds.width / 2.0f, bBounds.top + bBounds.height / 2.0f);
	float aHalf = a->getRadius();
	sf::Vector2f bHalf = sf::Vector2f(bBounds.width / 2.0f, bBounds.height / 2.0f);

	std::vector<sf::Vector2f> separationVectors;
	bool freeAxis = false;

	// X axis intersection
	float xIntersect = 0;
	if (aCenter.x > bCenter.x)
	{
		xIntersect = bCenter.x + bHalf.x - aCenter.x + aHalf;
		if (xIntersect > 0)
			separationVectors.push_back(sf::Vector2f(xIntersect, 0.0f));
	}
	else
	{
		xIntersect = aCenter.x + aHalf - bCenter.x + bHalf.x;
		if (xIntersect > 0)
			separationVectors.push_back(sf::Vector2f(-xIntersect, 0.0f));
	}
	if (xIntersect <= 0)
		freeAxis = true;

	// Y axis intersection
	if (!freeAxis)
	{
		float yIntersect = 0;
		if (aCenter.y > bCenter.y)
		{
			yIntersect = bCenter.y + bHalf.y - aCenter.y + aHalf;
			if (yIntersect > 0)
				separationVectors.push_back(sf::Vector2f(0.0f, yIntersect));
		}
		else
		{
			yIntersect = aCenter.y + aHalf - bCenter.y + bHalf.y;
			if (yIntersect > 0)
				separationVectors.push_back(sf::Vector2f(0.0f, -yIntersect));
		}
		if (yIntersect <= 0)
			freeAxis = true;
	}

	// Vertex intersections
	if (!freeAxis)
	{
		std::vector<sf::Vector2f> corners;
		corners.push_back(sf::Vector2f(bBounds.left, bBounds.top));
		corners.push_back(sf::Vector2f(bBounds.left + bBounds.width, bBounds.top));
		corners.push_back(sf::Vector2f(bBounds.left, bBounds.top + bBounds.height));
		corners.push_back(sf::Vector2f(bBounds.left + bBounds.width, bBounds.top + bBounds.height));

		for each (sf::Vector2f corner in corners)
		{
			sf::Vector2f delta = aCenter - corner;
			float deltaLength = sqrtf(delta.x * delta.x + delta.y * delta.y);
			if (delta.x > 0)
			{
				
			}
		}
	}

	if (!freeAxis)
	{
		sf::Vector2f smallestSeparator = sf::Vector2f();
		float separatorLength = FLT_MAX;
		for each (sf::Vector2f sep in separationVectors)
		{
			float vecLength = sqrtf(sep.x * sep.x + sep.y * sep.y);
			if (vecLength < separatorLength)
			{
				smallestSeparator = sep;
				separatorLength = vecLength;
			}
		}

		if (smallestSeparator.x != 0 || smallestSeparator.y != 0)
			a->Separate(smallestSeparator);
	}
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*gameArea, states);
	target.draw(*paddle, states);
	target.draw(*ball, states);
}
