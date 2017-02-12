#include "Game.hpp"
#include "Math.hpp"
#include "Collision.hpp"
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
	paddle->SetPosition((float)mousePos.x, paddle->GetPosition().y);

	ball->Update(delta);
	Collide(ball, paddle);
	Collide(ball, gameArea->leftWall);
	Collide(ball, gameArea->topWall);
	Collide(ball, gameArea->rightWall);
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
	target.draw(*gameArea, states);
	target.draw(*paddle, states);
	target.draw(*ball, states);
}
