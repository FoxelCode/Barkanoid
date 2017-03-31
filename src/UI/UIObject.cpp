#include "UI/UIObject.hpp"

#include "Collision/AABBCollider.hpp"

UIObject::UIObject(sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: GameObject(pos), size(size), align(align)
{
	collider = new AABBCollider(this, GetOffset(), size);
}

void UIObject::LoadGraphic(sf::Texture* tex)
{
	GameObject::LoadGraphic(tex);
	graphic->setPosition(GetOffset());
}

void UIObject::LoadSlicedGraphic(sf::Texture* tex)
{
	GameObject::LoadSlicedGraphic(tex);
	graphic->setPosition(GetOffset());
}

void UIObject::SetSize(sf::Vector2f size)
{
	this->size = size;
	UpdateSize();
}

sf::Vector2f UIObject::GetOffset() const
{
	sf::Vector2f offset;
	switch (align.horizontal)
	{
	case HorizontalAlign::Left:
		break;
	case HorizontalAlign::Middle:
		offset.x = -size.x / 2.0f;
		break;
	case HorizontalAlign::Right:
		offset.x = -size.x;
		break;
	}
	switch (align.vertical)
	{
	case VerticalAlign::Top:
		break;
	case VerticalAlign::Center:
		offset.y = -size.y / 2.0f;
		break;
	case VerticalAlign::Bottom:
		offset.y = -size.y;
		break;
	}
	return offset;
}

void UIObject::UpdateSize()
{
	static_cast<AABBCollider*>(collider)->setSize(size);
	static_cast<AABBCollider*>(collider)->SetOffset(GetOffset());
	if (graphic)
	{
		graphic->setPosition(GetOffset());
		graphic->SetSize(size);
	}
}
