#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"
#include "CircleCollider.hpp"

class Collision
{
public:
	static void Collide(Collider* a, Collider* b);
	static void PaddleCollide(CircleCollider* a, AABBCollider* b);

private:
	static void AABBToAABB(AABBCollider* a, AABBCollider* b);
	static void CircleToAABB(CircleCollider* a, AABBCollider* b);
};