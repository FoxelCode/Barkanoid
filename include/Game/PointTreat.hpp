#pragma once

#include "Treat.hpp"

class PointTreat : public Treat
{
public:
	PointTreat(sf::Vector2f pos, float launchAngle);

	void AddAward(PlayState* state);

private:
	int points;
};