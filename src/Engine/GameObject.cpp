#include "Engine/GameObject.hpp"

GameObject::~GameObject()
{
	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(sprite, states);
}

void GameObject::drawCollider(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (collider)
	{
		collider->Draw(target, states);
	}
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

void GameObject::SetFrame(int frame)
{
	SetTextureRect(sf::IntRect(frame * frameSize.x, 0, frameSize.x, frameSize.y));
}
