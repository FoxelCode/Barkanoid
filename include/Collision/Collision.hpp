#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"
#include "CircleCollider.hpp"

class Collision
{
public:
	static bool Collide(Collider* a, Collider* b);
	static bool PaddleCollide(CircleCollider* a, AABBCollider* b);

private:
	static bool AABBToAABB(AABBCollider* a, AABBCollider* b);
	static bool CircleToAABB(CircleCollider* a, AABBCollider* b);
};