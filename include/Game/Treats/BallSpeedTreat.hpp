#pragma once

#include "Treat.hpp"

class BallSpeedTreat : public Treat
{
public:
	enum Type
	{
		SpeedUp,
		SpeedDown
	};

	BallSpeedTreat(sf::Vector2f pos, float launchAngle, Type type);

	void AddAward(PlayState* state);

private:
	Type type;
	float speedChange;
};