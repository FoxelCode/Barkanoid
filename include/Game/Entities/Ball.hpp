#pragma once

#include "Engine/GameObject.hpp"
#include "Util/Tween.hpp"

class Ball : public GameObject
{
public:
	Ball(sf::Vector2f pos);
	~Ball();
	void Update(float delta);

	void Collided(GameObject* other, sf::Vector2f separationVelocity);

	void SetAngle(float angle);
	void SetVelocity(float velocity);
	void SetMoving(bool moving) { this->moving = moving; }
	float GetAngle() { return angle; }
	bool IsMoving() { return moving; }

	static const float SIZE;

private:
	float velocityMag;
	float angle;
	Tween::TweenInstance* tween;

	bool moving = true;
};