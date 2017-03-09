#pragma once

#include "Engine/GameObject.hpp"

class PlayState;

class Treat : public GameObject
{
public:
	Treat(sf::Vector2f pos, float launchAngle);
	virtual void Update(float delta);

	virtual void AddAward(PlayState* state) = 0;

private:
	float gravity;
};