#include "Wall.hpp"

#include "AABBCollider.hpp"
#include "Util.hpp"

Wall::Wall(sf::Vector2f pos, sf::Vector2f size)
	: GameObject(pos)
{
	SetTexture(Util::GetAssetManager()->GetTexture("wall.png"));
	texture->setRepeated(true);
	SetTextureRect(sf::IntRect(0, 0, size.x, size.y));
	collider = new AABBCollider(this, sf::Vector2f(), size);
}
