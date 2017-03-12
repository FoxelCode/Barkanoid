#include "Game/Entities/Ball.hpp"

#include <iostream>

#include "Util/Math.hpp"
#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Game/Entities/Paddle.hpp"
#include "Util/Tween.hpp"

const float Ball::SIZE = 12.0f;

Ball::Ball(sf::Vector2f pos)
	: GameObject(pos), velocityMag(400.0f), angle(0.5f)
{
	collider = new AABBCollider(this, sf::Vector2f(-Ball::SIZE / 2.0f, -Ball::SIZE / 2.0f), sf::Vector2f(Ball::SIZE, Ball::SIZE));

	tween = new Tween::TweenInstance(Ease::Type::QuadOut, 1.0f, 0.7f, 0.1f,
		[this](float v) { graphic->setScale(sf::Vector2f(v, v)); }, nullptr, Tween::Type::Boomerang, 0.0f);
	tween->Finish();
	Tween::Run(tween);

	LoadGraphic(G::GetAssetManager()->GetTexture("ball.png"), Graphic::Alignment::Center);

	SetAngle(angle);
}

Ball::~Ball()
{
	if (tween != nullptr)
	{
		Tween::RemoveTween(tween);
		delete tween;
		tween = nullptr;
	}
}

void Ball::Update(float delta)
{
	if (moving)
		GameObject::Update(delta);
}

void Ball::Collided(GameObject* other, sf::Vector2f separationVelocity)
{
	if (dynamic_cast<Paddle*>(other))
		SetAngle(reinterpret_cast<Paddle*>(other)->GetReflectionAngle(GetPosition()));
	else
		SetAngle(atan2f(separationVelocity.y, separationVelocity.x));
	tween->Reset();
	GameObject::Collided(other, Math::magnitude(separationVelocity) * Math::normalise(velocity));
}

void Ball::SetAngle(float angle)
{
	this->angle = angle;
	graphic->setRotation(angle * (180.0f / (float)PIELLO_DARKNESS_MY_OLD_FRIEND));
	sf::Vector2f dir = sf::Vector2f(cosf(angle), sinf(angle));
	velocity = dir * velocityMag;
}

void Ball::SetVelocity(float velocity)
{
	this->velocityMag = velocity;
	this->velocity = sf::Vector2f(cosf(angle), sinf(angle)) * velocity;
}
