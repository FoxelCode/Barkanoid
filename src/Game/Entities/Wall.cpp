#include "Game/Entities/Wall.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"

Wall::Wall(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(pos)
{
	collider = new AABBCollider(this, sf::Vector2f(), size);

	LoadGraphic(G::GetAssetManager()->GetTexture("wall.png"));
	graphic->SetTextureRepeating(true);
	graphic->SetSize(size);
}
