#include "Game/Util/TreatSpawner.hpp"

#include "Game/Entities/Treats/PaddleWidthTreat.hpp"
#include "Game/Entities/Treats/BallSpeedTreat.hpp"
#include "Game/Entities/Treats/MultiballTreat.hpp"
#include "Game/Entities/Treats/MagneticPaddleTreat.hpp"

const float TreatSpawner::powerupChance = 0.2f;
const float TreatSpawner::widthDownChance = 0.5f;
const float TreatSpawner::speedDownChance = 0.5f;

TreatSpawner::TreatSpawner()
{
	powerupTypes.Add(Treat::Type::PaddleWidth, 10.0f);
	powerupTypes.Add(Treat::Type::BallSpeed, 10.0f);
	powerupTypes.Add(Treat::Type::Multiball, 5.0f);
	powerupTypes.Add(Treat::Type::MagneticPaddle, 2.0f);
}

Treat* TreatSpawner::GetTreat(float launchAngle)
{
	// Check whether or not to spawn a powerup
	float pickPowerup = Random::Float(1.0f);
	
	// Spawn a powerup
	if (pickPowerup <= powerupChance)
	{
		// Pick a random powerup type to spawn
		Treat::Type randomPowerup = powerupTypes.GetRandom();
		switch (randomPowerup)
		{
		case Treat::PaddleWidth:
		{
			// Check whether to spawn a width down or up treat
			float pickWidthDir = Random::Float(1.0f);
			if (pickWidthDir <= widthDownChance)
				return new PaddleWidthTreat(sf::Vector2f(), launchAngle, PaddleWidthTreat::Type::WidthDown);
			return new PaddleWidthTreat(sf::Vector2f(), launchAngle, PaddleWidthTreat::Type::WidthUp);
		}

		case Treat::BallSpeed:
		{
			// Check whether to spawn a speed down or up treat
			float pickSpeedDir = Random::Float(1.0f);
			if (pickSpeedDir <= speedDownChance)
				return new BallSpeedTreat(sf::Vector2f(), launchAngle, BallSpeedTreat::Type::SpeedDown);
			return new BallSpeedTreat(sf::Vector2f(), launchAngle, BallSpeedTreat::Type::SpeedUp);
		}

		case Treat::Multiball:
			return new MultiballTreat(sf::Vector2f(), launchAngle);

		case Treat::MagneticPaddle:
			return new MagneticPaddleTreat(sf::Vector2f(), launchAngle);

		default:
			LOG_ERROR("Treat type " + std::to_string(randomPowerup) + " doesn't have spawning logic attached to it");
			return nullptr;
		}
	}
	return nullptr;
}
