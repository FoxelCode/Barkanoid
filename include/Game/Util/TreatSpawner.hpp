#pragma once

#include "Util/WeightedVector.hpp"
#include "Game/Entities/Treats/Treat.hpp"

class TreatSpawner
{
public:
	TreatSpawner();

	Treat* GetTreat(float launchAngle);

private:
	// Chance for a powerup to spawn in GetTreat().
	static const float powerupChance;
	static const float widthDownChance;
	static const float speedDownChance;

	WeightedVector<Treat::Type> powerupTypes;
};