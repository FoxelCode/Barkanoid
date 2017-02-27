#include "Game/PlayState.hpp"

#include "Engine/Input.hpp"
#include "Collision/Collision.hpp"
#include "Util/Random.hpp"

PlayState::PlayState()
	: State(), lives(2)
{
}

PlayState::~PlayState()
{
	if (ui != nullptr)
	{
		delete ui;
		ui = nullptr;
	}
}

void PlayState::Init()
{
	sf::Vector2u size = GetGame()->GetSize();

	ball = new Ball(sf::Vector2f(100.0f, 300.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 46.0f));
	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));
	level = new Level(sf::Vector2f(16.0f, 104.0f), sf::Vector2f((float)size.x - gameArea->GetWallThickness() * 2.0f, size.y));
	bgColour = level->GetBGColour();

	ui = new UI(size);

	sf::FloatRect levelBounds = level->GetCollider()->GetBounds();

	Add(ball);
	Add(paddle);
	Add(gameArea);
	Add(level);

	paddle->SetHorizontalRange(sf::Vector2f(16.0f, size.x - 16.0f));

	ResetLevel();
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	State::draw(target, states);
	target.draw(*ui, states);
}

void PlayState::Update(float delta)
{
	State::Update(delta);

	if (ball->IsMoving())
	{
		Collide(ball, paddle);
		State::Collide(ball, gameArea);
		State::Collide(ball, level);
	}

	// Check if the ball has passed the bottom of the screen -> lose a life
	if (ball->GetPosition().y > GetGame()->GetSize().y + ball->GetRadius())
	{
		ball->SetPosition(GetGame()->GetSize().x / 2.0f, GetGame()->GetSize().y / 2.0f);
		lives--;
		if (lives < 0)
		{
			level->ClearLevel();
			level->LoadLevel("level1");
			ResetLevel();
		}
		else
		{
			ResetLife();
		}
	}

	level->RemoveDead();
}

bool PlayState::Collide(Ball* a, Paddle* b)
{
	return Collision::PaddleCollide(static_cast<CircleCollider*>(a->GetCollider()), static_cast<AABBCollider*>(b->GetCollider()));
}

void PlayState::ResetLevel()
{
	lives = 2;
	ResetLife();
}

void PlayState::ResetLife()
{
	ui->SetLives(lives);
	ball->SetPosition(paddle->GetPosition().x + (Random::Float(paddle->GetSize().x / 2.0f) - paddle->GetSize().x / 4.0f), 0.0f);
	paddle->AttachBall(ball);
}
