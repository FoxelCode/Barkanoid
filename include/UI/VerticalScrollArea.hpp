#pragma once

#include "UI/UIObject.hpp"

class VerticalScrollArea : public UIObject
{
public:
	VerticalScrollArea(sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment());
	~VerticalScrollArea() {}
	virtual void Update(float delta);

	void AddChild(UIObject* child);

private:
	void SetCurrentScroll(float currentScroll);

	static const float scrollSpeed;

	std::vector<UIObject*> children;
	float currentScroll;
	float totalChildHeight;
	float maxScroll;
};