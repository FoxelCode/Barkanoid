#include "GameObject.hpp"

GameObject::~GameObject()
{
	delete collider;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	DrawSprite(target, states);
	if (collider)
	{
		DrawCollider(target, states);
	}
}

void GameObject::Update(float delta)
{
}

void GameObject::LoadTexture(std::string filename, float textureScale)
{
	texture.loadFromFile("res\\" + filename);
	sprite.setTexture(texture);
	this->textureScale = textureScale;
	sprite.setScale(textureScale, textureScale);
}

void GameObject::SetTextureRect(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
}

void GameObject::DrawCollider(sf::RenderTarget & target, sf::RenderStates states) const
{
	//collider->Draw(target, states);
}

void GameObject::DrawSprite(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
