#include "GameObject.hpp"

GameObject::~GameObject()
{
	delete collider;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(sprite, states);

#ifdef DRAW_COLLIDER
	if (collider)
	{
		collider->Draw(target, states);
	}
#endif
}

void GameObject::Update(float delta)
{
}

void GameObject::SetTexture(sf::Texture* tex, float textureScale)
{
	this->texture = tex;
	sprite.setTexture(*tex);
	this->textureScale = textureScale;
	sprite.setScale(textureScale, textureScale);
}

void GameObject::SetTextureRect(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}