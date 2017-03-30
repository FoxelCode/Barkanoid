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
	if (visible)
	{
		states.transform.translate(GetPosition());
		if (graphic != nullptr)
			target.draw(*graphic, states);
	}
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
	Move(velocity * delta);
}

void GameObject::Collided(GameObject* other, sf::Vector2f separationVelocity)
{
	Move(separationVelocity);
}

void GameObject::LoadGraphic(sf::Texture* tex, Graphic::Alignment align)
{
	graphic = new Graphic(align);
	graphic->SetTexture(tex);
}

void GameObject::LoadSlicedGraphic(sf::Texture* tex, Graphic::Alignment align)
{
	graphic = new SlicedGraphic(align);
	graphic->SetTexture(tex);
}