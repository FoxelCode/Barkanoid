#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"

class Collision
{
public:
	static sf::Vector2f Collide(Collider* a, Collider* b);

	static void SetDelta(float delta) { Collision::delta = delta; }

private:
	static sf::Vector2f AABBToAABB(AABBCollider* a, AABBCollider* b);
	static sf::FloatRect GetSweepBroadphaseRect(AABBCollider* a);
	static float SweepAABB(AABBCollider* a, AABBCollider* b, sf::Vector2f& normal);

	static float delta;
};