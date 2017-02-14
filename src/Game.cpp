#include "Game.hpp"

#include "Math.hpp"
#include "Collision.hpp"
#include "Util.hpp"
#include "Palette.hpp"

#include <vector>
#include <cfloat>
#include <iostream>
#include <SFML\Window\Mouse.hpp>

Game::Game(sf::RenderWindow& window, sf::Vector2u size)
	: window(&window), size(size)
{
	Util::SetAssetManager(&asset);

	ball = new Ball(sf::Vector2f(100.0f, 100.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 100.0f));
	gameArea = new GameArea(sf::Vector2f(), sf::Vector2f((float)size.x, (float)size.y));
	brick = new Brick(sf::Vector2f((float)size.x / 2.0f, 50.0f), Palette::Red);

	Add(ball);
	Add(paddle);
	Add(gameArea->leftWall);
	Add(gameArea->topWall);
	Add(gameArea->rightWall);
	Add(brick);
}

void Game::Update(float delta)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	paddle->SetPosition((float)mousePos.x, paddle->GetPosition().y);

	ball->Update(delta);
	Collide(ball, paddle);
	Collide(ball, gameArea->leftWall);
	Collide(ball, gameArea->topWall);
	Collide(ball, gameArea->rightWall);
	Collide(ball, brick);

	auto it = gameObjects.begin();
	while (it != gameObjects.end())
	{
		if (!(*it)->IsAlive())
		{
			GameObject* toErase = (*it);
			it = gameObjects.erase(it);
			delete toErase;
		}
		else
		{
			it++;
		}
	}
}

void Game::Add(GameObject* object)
{
	gameObjects.push_back(object);
}

void Game::Collide(GameObject* a, GameObject* b)
{
	Collision::Collide(a->GetCollider(), b->GetCollider());
}

void Game::Collide(Ball* a, Paddle* b)
{
	Collision::PaddleCollide(static_cast<CircleCollider*>(a->GetCollider()), static_cast<AABBCollider*>(b->GetCollider()));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (GameObject* object in gameObjects)
	{
		target.draw(*object, states);
	}
}
