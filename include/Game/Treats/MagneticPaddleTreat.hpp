#pragma once

#include "Treat.hpp"

class MagneticPaddleTreat : public Treat
{
public:
	MagneticPaddleTreat(sf::Vector2f pos, float launchAngle);

	void AddAward(PlayState* state);
};