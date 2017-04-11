#pragma once

#include "Collider.hpp"
#include "AABBCollider.hpp"

class Collision
{
public:
	/// <summary>
	/// <para>Collides two colliders together and separates them using sweeping if necessary.</para>
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if the two Colliders collided, false otherwise.</returns>
	static bool Collide(Collider* a, Collider* b);

	/// <summary>
	/// <para>Sets the delta timestep that the game runs at.</para>
	/// <para>This is required since collision calculation with sweeping has to know how much the objects move in one frame.</para>
	/// </summary>
	/// <param name="delta">Delta timestep (in seconds) that the game runs at.</param>
	static void SetDelta(float delta) { Collision::delta = delta; }

private:
	/// <summary>
	/// <para>Collides two AABBs together and separates them if necessary.</para>
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>True if the AABBColliders collided, false otherwise.</returns>
	static bool AABBToAABB(AABBCollider* a, AABBCollider* b);

	/// <summary>
	/// <para>Calculates a bounding box for an AABB's current position and its position in the next frame.</para>
	/// </summary>
	/// <param name="a"></param>
	/// <returns>Bounding box rectangle for the current and the next frame positions.</returns>
	static sf::FloatRect GetSweepBroadphaseRect(AABBCollider* a);

	/// <summary>
	/// <para>Sweeps the first AABB against the second, checking if it will collide during the next frame.</para>
	/// <para>If the two AABBs are already colliding, they will be separated using the shortest separating axis.</para>
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="normal">Separation normal, gets a non-zero value if a collision happened.</param>
	/// <returns>The time when the collision happened. A value between 0 and 1 means a collision happened this frame.</returns>
	static float SweepAABB(AABBCollider* a, AABBCollider* b, sf::Vector2f& normal);

	static float delta;
};