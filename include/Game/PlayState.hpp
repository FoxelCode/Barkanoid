#pragma once

#include "Engine/State.hpp"
#include "Engine/Game.hpp"
#include "GameArea.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Stage.hpp"
#include "UI.hpp"

class PlayState : public State
{
public:
	PlayState();
	~PlayState();
	
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
	Stage* stage = nullptr;
	UI* ui = nullptr;

	int lives;
};