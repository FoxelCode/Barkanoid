#pragma once

#include "Treat.hpp"

class PaddleWidthTreat : public Treat
{
public:
	enum Type
	{
		WidthUp,
		WidthDown
	};

	PaddleWidthTreat(sf::Vector2f pos, float launchAngle, Type type);

	void AddAward(PlayState* state);

private:
	Type type;
	float widthChange;
};