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
	void PostUpdate();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual void Add(GameObject* object);
	virtual void Remove(GameObject* object);
	bool Collide(GameObject* a, GameObject* b);

	void SetGame(Game* game);

	sf::Color GetBGColour() { return bgColour; }

protected:
	Game* GetGame() { return game; }

	sf::Color bgColour;

private:
	Game* game;
	std::vector<GameObject*> gameObjects;
};