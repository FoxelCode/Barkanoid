#pragma once

#include "Treat.hpp"

class MultiballTreat : public Treat
{
public:
	MultiballTreat(sf::Vector2f pos, float launchAngle);

	void AddAward(PlayState* state);
};