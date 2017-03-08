#pragma once

#include "Engine/GameObject.hpp"

class Ball : public GameObject
{
public:
	Ball(sf::Vector2f pos);

	void Separate(sf::Vector2f separation);

	void SetAngle(float angle);
	void SetVelocity(float velocity);
	void SetMoving(bool moving) { this->moving = moving; }
	float GetAngle() { return angle; }
	bool IsMoving() { return moving; }

	static const float SIZE;

private:
	float velocityMag;
	float angle;

	bool moving = true;
};