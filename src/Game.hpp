#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

#include "IUpdatable.hpp"
#include "GameArea.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Level.hpp"
#include "AssetManager.hpp"

class Game : public sf::Drawable, IUpdatable
{
public:
	Game(sf::RenderWindow& window, sf::Vector2u size);

	void Update(float delta);
	void Add(GameObject* object);
	void Collide(GameObject* a, GameObject* b);
	void Collide(Ball* a, Paddle* b);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	const sf::RenderWindow* window;
	sf::Vector2u size;
	sf::Color bgColour;

	AssetManager asset;

	std::vector<GameObject*> gameObjects;

	GameArea* gameArea = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	Level* level = nullptr;
};