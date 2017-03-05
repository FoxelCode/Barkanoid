#include "Game/States/PlayState.hpp"

#include "Engine/Input.hpp"
#include "Collision/Collision.hpp"
#include "Util/Random.hpp"
#include "Engine/G.hpp"
#include "Game/States/LevelSelectState.hpp"

PlayState::PlayState(std::string levelName)
	: State(), lives(2), levelName(levelName), ballSpeedIncrement(1.0f), ballSpeedBounds(300.0f, 800.0f),
	  ballSplitAngle((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 4.0f)
{
}

PlayState::~PlayState()
{
	SetMouseCaptured(false);

	if (level != nullptr)
	{
		delete level;
		level = nullptr;
	}
	if (ui != nullptr)
	{
		delete ui;
		ui = nullptr;
	}
	ClearScreens();
}

void PlayState::Init()
{
	SetMouseCaptured(true);
	sf::Vector2u size = GetGame()->GetSize();

	std::string levelData = G::GetAssetManager()->GetLevel(levelName);
	if (levelData == "")
	{
		LOG_ERROR("Trying to load level with no data");
		return;
	}
	level = new Level(levelData);

	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 46.0f));
	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));

	stage = new Stage(sf::Vector2f(16.0f, 104.0f), sf::Vector2f((float)size.x - gameArea->GetWallThickness() * 2.0f, (float)size.y));

	ui = new UI(size);

	Add(paddle);
	Add(gameArea);
	Add(stage);

	paddle->SetHorizontalRange(sf::Vector2f(16.0f, size.x - 16.0f));

	ResetLevel();
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	State::draw(target, states);
	target.draw(*ui, states);
	
	if (pauseScreen != nullptr)
		target.draw(*pauseScreen, states);
	if (stageCompleteScreen != nullptr)
		target.draw(*stageCompleteScreen, states);
	if (gameOverScreen != nullptr)
		target.draw(*gameOverScreen, states);
}

void PlayState::Update(float delta)
{
	if (!waiting)
	{
		State::Update(delta);

		// Collide balls
		for each (Ball* ball in balls)
		{
			if (ball->IsMoving())
			{
				Collide(ball, paddle);
				State::Collide(ball, gameArea);
				State::Collide(ball, stage);
			}
		}

		// Collide all treats and remove ones that have gone offscreen
		Treat* treat = nullptr;
		for (size_t i = 0; i < treats.size();)
		{
			treat = treats[i];
			State::Collide(treat, gameArea);
			bool hitPaddle = false;
			if (State::Collide(treat, paddle))
			{
				treat->AddAward(this);
				hitPaddle = true;
			}
			if (hitPaddle || treat->GetPosition().y - 50.0f > GetGame()->GetSize().y)
			{
				Remove(treat);
				delete treat;
			}
			else i++;
		}

		// Check for balls that have gone offscreen
		Ball* ball = nullptr;
		for (size_t i = 0; i < balls.size();)
		{
			ball = balls[i];
			if (ball->GetPosition().y > GetGame()->GetSize().y + ball->GetRadius())
			{
				Remove(ball);
				delete ball;
			}
			else i++;
		}

		// Increase ball speed
		int stageClockSeconds = (int)stageClock.getElapsedTime().asSeconds();
		float speedToAdd = 0.0f;
		while (stageClockSeconds > ballSpeedTimer)
		{
			ballSpeedTimer++;
			speedToAdd += ballSpeedIncrement;
		}
		if (speedToAdd > 0.0f)
			AddBallSpeed(speedToAdd);

		// Set UI timer
		ui->SetTime(stageClock.getElapsedTime());

		// Remove dead GameObjects
		stage->RemoveDead();

		// Check if there are no balls left -> lose a life
		if (balls.size() == 0)
		{
			lives--;
			if (lives < 0)
			{
				gameOverScreen = new GameOverScreen(GetGame()->GetSize(),
					std::bind(&PlayState::BackToLevelSelect, this),
					std::bind(&PlayState::GameOverResetLevel, this));
				waiting = true;
				SetMouseCaptured(false);
			}
			else
			{
				ResetLife();
			}
		}

		// Check if the stage has been completed
		if (stage->GetBrickCount() <= 0)
		{
			stageCompleteScreen = new StageCompleteScreen(GetGame()->GetSize(), level->GetStageName());
			stageCompleteScreen->SetCallback(std::bind(&PlayState::StageCompleteClicked, this));
			waiting = true;
			SetMouseCaptured(false);
		}

		//Check for pause keypress
		if (Input::JustPressed(sf::Keyboard::Escape) || Input::JustPressed(sf::Keyboard::P))
		{
			pauseScreen = new PauseScreen(GetGame()->GetSize(),
				std::bind(&PlayState::PauseContinueClicked, this),
				std::bind(&PlayState::BackToLevelSelect, this),
				std::bind(&PlayState::GameOverResetLevel, this));
			waiting = true;
			SetMouseCaptured(false);
		}
	}
	else
	{
		UpdateScreens(delta);
	}
}

void PlayState::Add(GameObject* object)
{
	if (object == nullptr)
	{
		LOG_WARNING("Trying to add nullptr to PlayState");
		return;
	}

	State::Add(object);

	if (dynamic_cast<Treat*>(object))
		treats.push_back(reinterpret_cast<Treat*>(object));
	if (dynamic_cast<Ball*>(object))
		balls.push_back(reinterpret_cast<Ball*>(object));
}

void PlayState::Remove(GameObject* object)
{
	if (object == nullptr)
	{
		LOG_WARNING("Trying to remove nullptr from PlayState");
		return;
	}

	State::Remove(object);

	if (dynamic_cast<Treat*>(object))
	{
		for (auto it = treats.begin(); it != treats.end(); it++)
		{
			if ((*it) == reinterpret_cast<Treat*>(object))
			{
				treats.erase(it);
				return;
			}
		}
	}
	if (dynamic_cast<Ball*>(object))
	{
		for (auto it = balls.begin(); it != balls.end(); it++)
		{
			if ((*it) == reinterpret_cast<Ball*>(object))
			{
				balls.erase(it);
				return;
			}
		}
	}
}

bool PlayState::Collide(Ball* a, Paddle* b)
{
	return Collision::PaddleCollide(static_cast<CircleCollider*>(a->GetCollider()), static_cast<AABBCollider*>(b->GetCollider()));
}

void PlayState::AddPoints(int points)
{
	this->points += points;
	ui->SetPoints(this->points);
}

void PlayState::SetPoints(int points)
{
	this->points = points;
	ui->SetPoints(this->points);
}

void PlayState::NextStage()
{
	std::string stageName = level->GetNextStage();
	// Return to level select if there are no stages left in the level
	if (stageName == "")
	{
		BackToLevelSelect();
		return;
	}

	stage->Load(G::GetAssetManager()->GetStage(levelName, stageName));
	bgColour = stage->GetBGColour();
	SetMouseCaptured(true);

	ClearTreats();
	ClearBalls();
	SetPoints(0);
	stageClock.restart();
	ballSpeedTimer = 0;
	ResetBallSpeed();
	ResetLife();
}

void PlayState::ResetLevel()
{
	lives = 2;
	level->Reset();
	paddle->Reset();
	NextStage();
}

void PlayState::ResetLife()
{
	ui->SetLives(lives);

	Ball* ball = new Ball(sf::Vector2f(100.0f, 300.0f));
	ball->SetPosition(paddle->GetPosition().x + (Random::Float(paddle->GetSize().x / 2.0f) - paddle->GetSize().x / 4.0f), 0.0f);
	Add(ball);

	paddle->SetMagnetic(false);
	paddle->AttachBall(ball);
}

void PlayState::ClearTreats()
{
	for (size_t i = 0; i < treats.size();)
	{
		if (treats[i] != nullptr)
		{
			Treat* treat = treats[i];
			if (treat != nullptr)
			{
				Remove(treat);
				delete treat;
			}
		}
	}
	treats.clear();
}

void PlayState::ClearBalls()
{
	for (size_t i = 0; i < balls.size();)
	{
		if (balls[i] != nullptr)
		{
			Ball* ball = balls[i];
			if (ball != nullptr)
			{
				Remove(ball);
				delete ball;
			}
		}
	}
	balls.clear();
}

void PlayState::UpdateScreens(float delta)
{
	if (pauseScreen != nullptr)
	{
		pauseScreen->Update(delta);
	}
	if (stageCompleteScreen != nullptr)
	{
		stageCompleteScreen->Update(delta);
	}
	if (gameOverScreen != nullptr)
	{
		gameOverScreen->Update(delta);
	}
}

void PlayState::ClearScreens()
{
	if (pauseScreen != nullptr)
	{
		delete pauseScreen;
		pauseScreen = nullptr;
	}
	if (stageCompleteScreen != nullptr)
	{
		delete stageCompleteScreen;
		stageCompleteScreen = nullptr;
	}
	if (gameOverScreen != nullptr)
	{
		delete gameOverScreen;
		gameOverScreen = nullptr;
	}
}

void PlayState::PauseContinueClicked()
{
	ClearScreens();
	waiting = false;
	SetMouseCaptured(true);
}

void PlayState::StageCompleteClicked()
{
	ClearScreens();
	waiting = false;
	NextStage();
}

void PlayState::BackToLevelSelect()
{
	LevelSelectState* state = new LevelSelectState();
	GetGame()->SwitchState(state);
}

void PlayState::GameOverResetLevel()
{
	ClearScreens();
	waiting = false;
	ResetLevel();
}

void PlayState::SetMouseCaptured(bool captured)
{
	GetGame()->GetWindow()->setMouseCursorGrabbed(captured);
	GetGame()->GetWindow()->setMouseCursorVisible(!captured);
}

void PlayState::AddBallSpeed(float amount)
{
	ballSpeed += amount;
	ballSpeed = Math::clamp(ballSpeed, ballSpeedBounds.x, ballSpeedBounds.y);
	UpdateBallSpeed();
}

void PlayState::UpdateBallSpeed()
{
	for each (Ball* ball in balls)
	{
		ball->SetVelocity(ballSpeed);
	}
}

void PlayState::ResetBallSpeed()
{
	ballSpeed = 400.0f;
	UpdateBallSpeed();
}

void PlayState::SplitBalls()
{
	size_t currentBallCount = balls.size();
	for (size_t i = 0; i < currentBallCount; i++)
	{
		Ball* ball = balls[i];
		float ballAngle = ball->GetAngle();
		ball->SetAngle(ballAngle - ballSplitAngle / 2.0f);

		Ball* newBall = new Ball(ball->GetPosition());
		newBall->SetVelocity(ballSpeed);
		newBall->SetAngle(ballAngle + ballSplitAngle / 2.0f);
		Add(newBall);
	}
}
