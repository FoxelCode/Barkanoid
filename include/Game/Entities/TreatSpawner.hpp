#pragma once

#include "Util/WeightedVector.hpp"
#include "Treats/Treat.hpp"

class TreatSpawner
{
public:
	TreatSpawner();

	Treat* GetTreat(float launchAngle);

private:
	static const float powerupChance;
	static const float widthDownChance;
	static const float speedDownChance;

	WeightedVector<Treat::Type> powerupTypes;
};