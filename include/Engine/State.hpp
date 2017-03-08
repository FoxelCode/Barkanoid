#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "IUpdatable.hpp"
#include "GameObject.hpp"
class Game;

class State : public sf::Drawable, IUpdatable
{
public:
	State();
	virtual ~State();
	virtual void Init() {};
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual void Add(GameObject* object);
	virtual void Remove(GameObject* object);
	sf::Vector2f Collide(GameObject* a, GameObject* b);

	void SetGame(Game* game);

protected:
	Game* GetGame() { return game; }

	sf::Color bgColour;

private:
	Game* game;
	std::vector<GameObject*> gameObjects;
};