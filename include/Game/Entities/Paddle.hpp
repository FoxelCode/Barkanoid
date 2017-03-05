#pragma once

#include <SFML\Graphics\RectangleShape.hpp>

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Entities/Ball.hpp"

class Paddle : public GameObject
{
public:
	Paddle(sf::Vector2f pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void Collided(GameObject* other);

	void SetWidth(float width);
	void SetHorizontalRange(sf::Vector2f range) { horizontalRange = range; }
	void SetMagnetic(bool magnetic) { this->magnetic = magnetic; }
	sf::Vector2f GetSize() const { return size; }
	float GetReflectionScalar(sf::Vector2f pos);
	float GetAngleRange() { return angleRange * ((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 180.0f); }

	void AttachBall(Ball* ball);
	void AddWidth(float width);

private:
	sf::Vector2f size;
	sf::Vector2f widthBounds;
	sf::Vector2f horizontalRange;
	float angleRange;
	
	bool magnetic;
	std::vector<std::pair<Ball*, float>> attachedBalls;
};