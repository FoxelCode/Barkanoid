#pragma once

#include "Engine/State.hpp"
#include "Engine/Game.hpp"
#include "GameArea.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Level.hpp"
#include "UI.hpp"

class Barkanoid : public State
{
public:
	Barkanoid();
	~Barkanoid();
	
	void Init();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void Update(float delta);

	bool Collide(Ball* a, Paddle* b);
	void ResetLevel();
	void ResetLife();

private:
	GameArea* gameArea = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	Level* level = nullptr;
	UI* ui = nullptr;

	int lives;
};