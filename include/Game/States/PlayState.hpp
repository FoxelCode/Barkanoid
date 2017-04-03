#pragma once

#include "Engine/State.hpp"
#include "Engine/Game.hpp"
#include "Game/Entities/GameArea.hpp"
#include "Game/Entities/Ball.hpp"
#include "Game/Entities/Paddle.hpp"
#include "Game/Entities/Level.hpp"
#include "Game/Entities/Stage.hpp"
#include "Game/Entities/Treats/Treat.hpp"
#include "Game/Entities/UI.hpp"
#include "Game/Screens/PauseScreen.hpp"
#include "Game/Screens/StageCompleteScreen.hpp"
#include "Game/Screens/GameOverScreen.hpp"
#include "Game/Util/TreatSpawner.hpp"

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

	void AddPoints(int points);
	void SetPoints(int points);

	void NextStage();
	void ResetLevel();
	void ResetLife();
	void ClearTreats();
	void ClearBalls();

	void UpdateScreens(float delta);
	void ClearScreens();

	void PauseContinueClicked();
	void StageCompleteClicked();
	void BackToLevelSelect();
	void GameOverResetLevel();

	void SetMouseCaptured(bool captured);

	void AddBallSpeed(float amount);
	void UpdateBallSpeed();
	void ResetBallSpeed();
	void SplitBalls();

	Paddle* GetPaddle() { return paddle; }
	TreatSpawner& GetTreatSpawner() { return treatSpawner; }

private:
	GameArea* gameArea = nullptr;
	std::vector<Ball*> balls;
	Paddle* paddle = nullptr;
	std::string levelName;
	Level* level = nullptr;
	Stage* stage = nullptr;
	TreatSpawner treatSpawner;
	std::vector<Treat*> treats;
	UI* ui = nullptr;

	PauseScreen* pauseScreen = nullptr;
	StageCompleteScreen* stageCompleteScreen = nullptr;
	GameOverScreen* gameOverScreen = nullptr;
	bool waiting = false;

	int lives;
	int totalPoints;
	int stagePoints;
	sf::Time stageTime;

	float ballSpeed;
	int ballSpeedTimer;
	float ballSpeedIncrement;
	sf::Vector2f ballSpeedBounds;
	float ballSplitAngle;
};