#include "Paddle.hpp"

#include "AABBCollider.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: GameObject(), angleRange(160.0f)
{
	SetPosition(pos);
	size = sf::Vector2f(60.0f, 16.0f);
	collider = new AABBCollider(this, sf::Vector2f(-30.0f, -8.0f), size);

	LoadTexture("paddle.png");
	sf::Vector2i sliceSize = sf::Vector2i(16, 16);
	SetTextureRect(sf::IntRect(sliceSize.x, 0, sliceSize.x, sliceSize.y));
	sprite.setScale((size.x - sliceSize.x * 2.0f * textureScale) / sliceSize.x, textureScale);
	sprite.setPosition(-size.x / 2.0f + sliceSize.x * textureScale, -size.y / 2.0f);
	leftSide.setTexture(texture);
	leftSide.setTextureRect(sf::IntRect(0, 0, sliceSize.x, sliceSize.y));
	leftSide.setScale(textureScale, textureScale);
	leftSide.setPosition(-size.x / 2.0f, -size.y / 2.0f);
	rightSide.setTexture(texture);
	rightSide.setTextureRect(sf::IntRect(sliceSize.x * 2, 0, sliceSize.x, sliceSize.y));
	rightSide.setScale(textureScale, textureScale);
	rightSide.setPosition(size.x / 2.0f - sliceSize.x * textureScale, -size.y / 2.0f);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	DrawSprite(target, states);
	target.draw(leftSide, states);
	target.draw(rightSide, states);
	if (collider)
	{
		DrawCollider(target, states);
	}
}

float Paddle::GetReflectionScalar(sf::Vector2f pos)
{
	return fmaxf(fminf((pos.x - GetPosition().x) / size.x, 1.0f), -1.0f);
}
