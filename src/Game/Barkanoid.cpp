#include "Game/Barkanoid.hpp"

#include "Engine/Input.hpp"
#include "Collision/Collision.hpp"

Barkanoid::Barkanoid(sf::RenderWindow& window, sf::Vector2u size)
	: Game(window, size), lives(2)
{
	ball = new Ball(sf::Vector2f(100.0f, 300.0f));
	paddle = new Paddle(sf::Vector2f((float)size.x / 2.0f, (float)size.y - 46.0f));
	gameArea = new GameArea(sf::Vector2f(0.0f, 64.0f), sf::Vector2f((float)size.x, (float)size.y - 64.0f));
	level = new Level(sf::Vector2f(16.0f, 104.0f), sf::Vector2f());
	bgColour = level->GetBGColour();

	ui = new UI(size);

	sf::FloatRect levelBounds = level->GetCollider()->GetBounds();

	Add(ball);
	Add(paddle);
	Add(gameArea);
	Add(level);

	Reset();
}

Barkanoid::~Barkanoid()
{
	if (gameArea != nullptr)
	{
		delete gameArea;
		gameArea = nullptr;
	}
	if (ball != nullptr)
	{
		delete ball;
		ball = nullptr;
	}
	if (paddle != nullptr)
	{
		delete paddle;
		paddle = nullptr;
	}
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
}

void Barkanoid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Game::draw(target, states);
	target.draw(*ui, states);
}

void Barkanoid::Update(float delta)
{
	Game::Update(delta);

	Collide(ball, paddle);
	Game::Collide(ball, gameArea);
	Game::Collide(ball, level);

	// Check if the ball has passed the bottom of the screen -> lose a life
	if (ball->GetPosition().y > size.y + ball->GetRadius())
	{
		ball->SetPosition(size.x / 2.0f, size.y / 2.0f);
		lives--;
		if (lives < 0)
		{
			level->ClearLevel();
			level->LoadLevel("level1");
			Reset();
		}
		else
		{
			ui->SetLives(lives);
		}
	}

	// Restrict paddle movement to the game area
	float paddleX = Math::clamp(paddle->GetPosition().x, 16.0f + paddle->GetCollider()->GetBounds().width / 2.0f,
		size.x - 16.0f - paddle->GetCollider()->GetBounds().width / 2.0f);
	paddle->SetPosition(paddleX, paddle->GetPosition().y);
}

void Barkanoid::Collide(Ball* a, Paddle* b)
{
	Collision::PaddleCollide(static_cast<CircleCollider*>(a->GetCollider()), static_cast<AABBCollider*>(b->GetCollider()));
}

void Barkanoid::Reset()
{
	lives = 2;
	ui->SetLives(lives);
	//ball->SetPosition(sf::Vector2f(paddle->GetPosition().x, paddle->GetPosition().y ))
}
