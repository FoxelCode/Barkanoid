#pragma once

#include "Engine\Game.hpp"
#include "GameArea.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Level.hpp"
#include "UI.hpp"

class Barkanoid : public Game
{
public:
	Barkanoid(sf::RenderWindow& window, sf::Vector2u size);
	~Barkanoid();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void Update(float delta);
	void Collide(Ball* a, Paddle* b);
	void Reset();

private:
	GameArea* gameArea = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	Level* level = nullptr;
	UI* ui = nullptr;

	int lives;
};