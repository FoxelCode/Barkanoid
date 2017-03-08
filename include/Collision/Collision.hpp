#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"

class Collision
{
public:
	static sf::Vector2f Collide(Collider* a, Collider* b);

private:
	static sf::Vector2f AABBToAABB(AABBCollider* a, AABBCollider* b);
	static float SweepAABB(AABBCollider* a, AABBCollider* b, sf::Vector2f& normal);
};