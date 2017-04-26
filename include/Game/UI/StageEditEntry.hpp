#pragma once

#include "UI/UIObject.hpp"
#include "UI/MultilineText.hpp"
#include "UI/Button.hpp"

class StageEditEntry : public UIObject
{
public:
	StageEditEntry(std::string stageName, ButtonStringCallback editButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment());
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(float delta);

private:
	static const sf::Vector2f padding;
	static const float editButtonWidth;
	static const float editButtonSpacing;

	MultilineText* stageName;
	Button* editButton;
};