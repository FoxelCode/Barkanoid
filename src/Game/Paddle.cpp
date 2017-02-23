#include "Game/Paddle.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Engine/Input.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: GameObject(pos), angleRange(160.0f)
{
	size = sf::Vector2f(60.0f, 12.0f);
	collider = new AABBCollider(this, sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f), size);

	SetTexture(G::GetAssetManager()->GetTexture("paddle.png"), 2.0f);
	sf::Vector2i sliceSize = sf::Vector2i(6, 6);
	SetTextureRect(sf::IntRect(sliceSize.x, 0, sliceSize.x, sliceSize.y));
	leftSide.setTexture(*texture);
	leftSide.setScale(textureScale, textureScale);
	rightSide.setTexture(*texture);
	rightSide.setScale(textureScale, textureScale);

	SetWidth(size.x);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(sprite, states);
	target.draw(leftSide, states);
	target.draw(rightSide, states);
}

void Paddle::Update(float delta)
{
	sf::Vector2f mousePos = sf::Vector2f((float)Input::GetMousePosition().x, GetPosition().y);
	sf::Vector2f mouseDelta = mousePos - GetPosition();
	Move(mouseDelta);
}

void Paddle::SetWidth(float width)
{
	size.x = width;
	AABBCollider* coll = static_cast<AABBCollider*>(collider);
	coll->SetOffset(sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f));
	coll->setSize(size);

	sf::Vector2i sliceSize = sf::Vector2i(6, 6);
	sprite.setScale((size.x - sliceSize.x * 2.0f * textureScale) / sliceSize.x, textureScale);
	sprite.setPosition(-size.x / 2.0f + sliceSize.x * textureScale, -size.y / 2.0f);

	leftSide.setTextureRect(sf::IntRect(0, 0, sliceSize.x, sliceSize.y));
	leftSide.setPosition(-size.x / 2.0f, -size.y / 2.0f);
	rightSide.setTextureRect(sf::IntRect(sliceSize.x * 2, 0, sliceSize.x, sliceSize.y));
	rightSide.setPosition(size.x / 2.0f - sliceSize.x * textureScale, -size.y / 2.0f);
}

float Paddle::GetReflectionScalar(sf::Vector2f pos)
{
	return fmaxf(fminf((pos.x - GetPosition().x) / size.x, 1.0f), -1.0f);
}