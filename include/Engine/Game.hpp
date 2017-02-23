#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

#include "IUpdatable.hpp"
#include "GameObject.hpp"
#include "AssetManager.hpp"

class Game : public sf::Drawable, IUpdatable
{
public:
	Game(sf::RenderWindow& window, sf::Vector2u size);
	~Game();

	virtual void Update(float delta);
	void Add(GameObject* object);
	void Collide(GameObject* a, GameObject* b);

	void HandleEvent(sf::Event evt);

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	const sf::RenderWindow* window;
	sf::Vector2u size;
	sf::Color bgColour;

	bool paused = false;
	bool showColliders = false;
	bool allowStep = false;

	std::vector<GameObject*> gameObjects;

private:
	AssetManager asset;
};