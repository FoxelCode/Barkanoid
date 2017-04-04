#pragma once

#include <SFML\Graphics\RectangleShape.hpp>

#include "Engine/GameObject.hpp"
#include "Util/Math.hpp"
#include "Game/Entities/Ball.hpp"

class Paddle : public GameObject
{
public:
	Paddle(sf::Vector2f pos);
	~Paddle();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void Collided(GameObject* other);

	void SetWidth(float width);
	void SetHorizontalRange(sf::Vector2f range) { horizontalRange = range; }
	void SetMagnetic(bool magnetic) { this->magnetic = magnetic; }
	sf::Vector2f GetSize() const { return size; }
	float GetReflectionAngle(sf::Vector2f pos);

	void AttachBall(Ball* ball);
	void AddWidth(float width);
	void Reset();

private:
	sf::Vector2f size;
	sf::Vector2f widthBounds;
	sf::Vector2f horizontalRange;
	float topAngleRange;
	float extraAngleRange;
	Tween::TweenInstance* tween;
	
	bool magnetic;
	std::vector<std::pair<Ball*, float>> attachedBalls;
};