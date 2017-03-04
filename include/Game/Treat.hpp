#pragma once

#include "Engine/GameObject.hpp"

class Treat : public GameObject
{
public:
	Treat(sf::Vector2f pos, float launchAngle);
	virtual void Update(float delta);

	void Separate(sf::Vector2f separation);

private:
	sf::Vector2f velocity;
	float gravity;
};