#pragma once

#include "Engine/State.hpp"
#include "Engine/Game.hpp"
#include "GameArea.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Level.hpp"
#include "Stage.hpp"
#include "Treats/Treat.hpp"
#include "UI.hpp"
#include "StageCompleteScreen.hpp"
#include "GameOverScreen.hpp"

class PlayState : public State
{
public:
	PlayState(std::string levelName);
	~PlayState();
	
	void Init();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void Update(float delta);

	void Add(GameObject* object);
	void Remove(GameObject* object);
	bool Collide(Ball* a, Paddle* b);

	void AddPoints(int points);
	void SetPoints(int points);

	void NextStage();
	void ResetLevel();
	void ResetLife();
	void ClearTreats();
	void ClearBalls();

	void StageCompleteClicked();
	void BackToLevelSelect();
	void GameOverResetLevel();

	void SetMouseCaptured(bool captured);

	void AddBallSpeed(float amount);
	void UpdateBallSpeed();
	void ResetBallSpeed();
	void SplitBalls();

	Paddle* GetPaddle() { return paddle; }

private:
	GameArea* gameArea = nullptr;
	std::vector<Ball*> balls;
	Paddle* paddle = nullptr;
	std::string levelName;
	Level* level = nullptr;
	Stage* stage = nullptr;
	std::vector<Treat*> treats;
	UI* ui = nullptr;

	StageCompleteScreen* stageCompleteScreen = nullptr;
	GameOverScreen* gameOverScreen = nullptr;
	bool waiting = false;

	int lives;
	int points;
	sf::Clock stageClock;

	float ballSpeed;
	int ballSpeedTimer;
	float ballSpeedIncrement;
	sf::Vector2f ballSpeedBounds;
	float ballSplitAngle;
};