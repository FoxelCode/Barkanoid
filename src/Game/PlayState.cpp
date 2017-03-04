#include "Game/PlayState.hpp"

#include "Engine/Input.hpp"
#include "Collision/Collision.hpp"
#include "Util/Random.hpp"
#include "Engine/G.hpp"
#include "Game/LevelSelectState.hpp"

PlayState::PlayState(std::string levelName)
	: State(), lives(2), levelName(levelName)
{
}

PlayState::~PlayState()
{
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

void PlayState::Init()
{
	sf::Vector2u size = GetGame()->GetSize();

	std::string levelData = G::GetAssetManager()->GetLevel(levelName);
	if (levelData == "")
	{
		LOG_ERROR("Trying to load level with no data");
		return;
	}
	level = new Level(levelData);

	ball = new Ball(sf::Vector2f(100.0f, 300.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 46.0f));
	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));

	stage = new Stage(sf::Vector2f(16.0f, 104.0f), sf::Vector2f((float)size.x - gameArea->GetWallThickness() * 2.0f, (float)size.y));

	ui = new UI(size);

	Add(ball);
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

		if (ball->IsMoving())
		{
			Collide(ball, paddle);
			State::Collide(ball, gameArea);
			State::Collide(ball, stage);
		}

		// Collide all treats with the level and remove ones that have gone offscreen
		Treat* treat = nullptr;
		for (size_t i = 0; i < treats.size(); i++)
		{
			treat = treats[i];
			State::Collide(treat, gameArea);
			if (treat->GetPosition().y - 50.0f > GetGame()->GetSize().y)
			{
				Remove(treat);
				delete treat;
			}
		}

		// Check if the ball has passed the bottom of the screen -> lose a life
		if (ball->GetPosition().y > GetGame()->GetSize().y + ball->GetRadius())
		{
			ball->SetPosition(GetGame()->GetSize().x / 2.0f, GetGame()->GetSize().y / 2.0f);
			lives--;
			if (lives < 0)
			{
				gameOverScreen = new GameOverScreen(GetGame()->GetSize(),
					std::bind(&PlayState::BackToLevelSelect, this),
					std::bind(&PlayState::GameOverResetLevel, this));
				waiting = true;
			}
			else
			{
				ResetLife();
			}
		}

		ui->SetTime(stageClock.getElapsedTime());

		stage->RemoveDead();

		// Check if the stage has been completed
		if (stage->GetBrickCount() <= 0)
		{
			stageCompleteScreen = new StageCompleteScreen(GetGame()->GetSize(), level->GetStageName());
			stageCompleteScreen->SetCallback(std::bind(&PlayState::StageCompleteClicked, this));
			waiting = true;
		}
	}
	else
	{
		if (stageCompleteScreen != nullptr)
		{
			stageCompleteScreen->Update(delta);
		}
		if (gameOverScreen != nullptr)
		{
			gameOverScreen->Update(delta);
		}
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
}

bool PlayState::Collide(Ball* a, Paddle* b)
{
	return Collision::PaddleCollide(static_cast<CircleCollider*>(a->GetCollider()), static_cast<AABBCollider*>(b->GetCollider()));
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

	stageClock.restart();
	ResetLife();
}

void PlayState::ResetLevel()
{
	lives = 2;
	level->Reset();
	NextStage();
}

void PlayState::ResetLife()
{
	ui->SetLives(lives);
	ball->SetPosition(paddle->GetPosition().x + (Random::Float(paddle->GetSize().x / 2.0f) - paddle->GetSize().x / 4.0f), 0.0f);
	paddle->AttachBall(ball);
}

void PlayState::StageCompleteClicked()
{
	if (stageCompleteScreen != nullptr)
	{
		delete stageCompleteScreen;
		stageCompleteScreen = nullptr;
	}
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
	if (gameOverScreen != nullptr)
	{
		delete gameOverScreen;
		gameOverScreen = nullptr;
	}
	waiting = false;
	ResetLevel();
}
