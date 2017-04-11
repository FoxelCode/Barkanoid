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
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->IsActive())
			gameObjects[i]->Update(delta);
	}
}

void State::PostUpdate()
{
	for (size_t i = 0; i < gameObjects.size(); )
	{
		if (!gameObjects[i]->IsAlive())
		{
			GameObject* object = gameObjects[i];
			Remove(object);
			delete object;
		}
		else
			i++;
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
	if (object == nullptr)
	{
		LOG_WARNING("Trying to add nullptr to State");
		return;
	}

	gameObjects.push_back(object);
}

void State::Remove(GameObject* object)
{
	if (object == nullptr)
	{
		LOG_WARNING("Trying to remove nullptr from State");
		return;
	}

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		if ((*it) == object)
		{
			gameObjects.erase(it);
			return;
		}
	}
}

bool State::Collide(GameObject* a, GameObject* b)
{
	return Collision::Collide(a->GetCollider(), b->GetCollider());
}

void State::SetGame(Game* game)
{
	ASSERT(game != nullptr);
	this->game = game;
}
