#pragma once

#include "Engine/GameObject.hpp"

class Ball : public GameObject
{
public:
	Ball(sf::Vector2f pos);

	void Update(float delta);
	void Separate(sf::Vector2f separation);

	void SetAngle(float angle);
	void SetVelocity(float velocity);
	float GetRadius();

private:
	sf::Vector2f velocityVec;
	float velocity;
	float angle;
};