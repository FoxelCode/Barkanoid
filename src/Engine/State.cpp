#include "Engine/State.hpp"

#include "Engine/Game.hpp"
#include "Collision/Collision.hpp"

State::State()
	: bgColour(sf::Color::Black)
{
}

State::~State()
{
	for (int i = gameObjects.size() - 1; i >= 0; i--)
	{
		if (gameObjects[i] != nullptr)
		{
			delete gameObjects[i];
			gameObjects[i] = nullptr;
		}
	}
	gameObjects.clear();
}

void State::Update(float delta)
{
	for each (GameObject* object in gameObjects)
	{
		if (object->IsActive())
			object->Update(delta);
	}
}

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(bgColour);
	for each (GameObject* object in gameObjects)
	{
		target.draw(*object, states);
		if (game->IsShowColliders())
			object->DrawCollider(target, states);
	}
}

void State::Add(GameObject* object)
{
	gameObjects.push_back(object);
}

void State::Remove(GameObject* object)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		if ((*it) == object)
		{
			gameObjects.erase(it);
			return;
		}
	}
}

void State::Collide(GameObject* a, GameObject* b)
{
	Collision::Collide(a->GetCollider(), b->GetCollider());
}

void State::SetGame(Game* game)
{
	ASSERT(game != nullptr);
	this->game = game;
}
