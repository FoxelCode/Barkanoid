#include "Engine/Game.hpp"

#include "Util/Math.hpp"
#include "Collision/Collision.hpp"
#include "Engine/G.hpp"
#include "Game/Palette.hpp"
#include "Engine/Input.hpp"

#include <vector>
#include <cfloat>
#include <iostream>

#include <SFML\Window\Event.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

Game::Game(sf::RenderWindow& window, sf::Vector2u size)
	: window(&window), size(size), bgColour(Palette::Black)
{
	G::SetAssetManager(&asset);
	Input::SetWindow(&window);

	window.setKeyRepeatEnabled(false);
}

Game::~Game()
{
	gameObjects.clear();
}

void Game::Update(float delta)
{
	if (Input::JustPressed(sf::Keyboard::P))
		paused = !paused;
	if (Input::JustPressed(sf::Keyboard::O))
		showColliders = !showColliders;

	if (!paused || allowStep)
	{
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

		for each (GameObject* object in gameObjects)
		{
			if (object->IsActive())
				object->Update(delta);
		}

		allowStep = false;
	}
	else
	{
		if (Input::JustPressed(sf::Keyboard::N))
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
		if (showColliders)
			(*object).drawCollider(target, states);
	}
}
