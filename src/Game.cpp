#include "Game.hpp"

#include "Math.hpp"
#include "Collision.hpp"
#include "Util.hpp"
#include "Palette.hpp"
#include "Input.hpp"

#include <vector>
#include <cfloat>
#include <iostream>

#include <SFML\Window\Event.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

Game::Game(sf::RenderWindow& window, sf::Vector2u size)
	: window(&window), size(size), bgColour(Palette::Black)
{
	Util::SetAssetManager(&asset);

	window.setKeyRepeatEnabled(false);

	ball = new Ball(sf::Vector2f(100.0f, 300.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 46.0f));
	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));
	level = new Level(sf::Vector2f(16.0f, 104.0f), sf::Vector2f());
	bgColour = level->GetBGColour();

	sf::FloatRect levelBounds = level->GetCollider()->GetBounds();

	Add(ball);
	Add(paddle);
	Add(gameArea);
	Add(level);
}

void Game::Update(float delta)
{
	if (Input::JustPressed(sf::Keyboard::P))
		paused = !paused;

	if (!paused || allowStep)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		paddle->SetPosition((float)mousePos.x, paddle->GetPosition().y);

		for each (GameObject* object in gameObjects)
			object->Update(delta);

		Collide(ball, paddle);
		Collide(ball, gameArea);
		Collide(ball, level);

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
		allowStep = false;
	}
	else
	{
		if (Input::JustPressed(sf::Keyboard::S))
			allowStep = true;
	}
	Input::Update();
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

void Game::HandleEvent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed || evt.type == sf::Event::KeyReleased)
		Input::HandleEvent(evt);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(bgColour);
	for each (GameObject* object in gameObjects)
	{
		target.draw(*object, states);
	}
}
