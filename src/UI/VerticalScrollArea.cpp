#include "UI/VerticalScrollArea.hpp"

#include "Engine/Input.hpp"
#include "Util/Math.hpp"

const float VerticalScrollArea::scrollSpeed = 20.0f;

VerticalScrollArea::VerticalScrollArea(sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align), currentScroll(0.0f), totalChildHeight(0.0f), maxScroll(0.0f)
{
}

void VerticalScrollArea::Update(float delta)
{
	UIObject::Update(delta);

	float scrollDelta = Input::GetMouseScrollDelta();
	if (scrollDelta != 0.0f)
	{
		currentScroll += -scrollDelta * scrollSpeed;
		SetCurrentScroll(Math::clamp(currentScroll, 0.0f, maxScroll));
	}
}

void VerticalScrollArea::AddChild(UIObject* child)
{
	children.push_back(child);
	child->SetPosition(GetPosition().x + GetOffset().x - child->GetOffset().x, GetPosition().y + totalChildHeight);
	totalChildHeight += child->GetSize().y;

	float scrollableHeight = totalChildHeight - size.y;
	if (scrollableHeight > 0.0f)
		maxScroll = scrollableHeight;
}

void VerticalScrollArea::SetCurrentScroll(float currentScroll)
{
	this->currentScroll = currentScroll;

	float currentHeight = 0.0f;
	for (UIObject* child : children)
	{
		child->SetPosition(child->GetPosition().x, GetPosition().y - currentScroll + currentHeight);
		currentHeight += child->GetSize().y;
	}
}
