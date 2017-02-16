#include "Wall.hpp"

#include "AABBCollider.hpp"
#include "Util.hpp"

Wall::Wall(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(pos)
{
	SetTexture(Util::GetAssetManager()->GetTexture("wall.png"), 2.0f);
	texture->setRepeated(true);
	SetTextureRect(sf::IntRect(0, 0, size.x / textureScale, size.y / textureScale));
	collider = new AABBCollider(this, sf::Vector2f(), size);
}
