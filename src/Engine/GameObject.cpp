#include "Engine/GameObject.hpp"

#include "Graphics/SlicedGraphic.hpp"

GameObject::~GameObject()
{
	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}
	if (graphic != nullptr)
	{
		delete graphic;
		graphic = nullptr;
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	if (graphic != nullptr)
		target.draw(*graphic, states);
}

void GameObject::DrawCollider(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (collider)
	{
		collider->Draw(target, states);
	}
}

void GameObject::Update(float delta)
{
}

void GameObject::LoadGraphic(sf::Texture* tex)
{
	graphic = new Graphic();
	graphic->SetTexture(tex);
}

void GameObject::LoadSlicedGraphic(sf::Texture* tex)
{
	graphic = new SlicedGraphic();
	graphic->SetTexture(tex);
}

//void GameObject::SetTexture(sf::Texture* tex, float textureScale)
//{
//	this->texture = tex;
//	sprite.setTexture(*tex);
//	this->textureScale = textureScale;
//	sprite.setScale(textureScale, textureScale);
//}
//
//void GameObject::SetTextureRect(sf::IntRect rect)
//{
//	sprite.setTextureRect(rect);
//}
//
//void GameObject::SetFrame(int frame)
//{
//	SetTextureRect(sf::IntRect(frame * frameSize.x, 0, frameSize.x, frameSize.y));
//}