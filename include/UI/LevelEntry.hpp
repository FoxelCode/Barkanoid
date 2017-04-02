#pragma once

#include "Game/Entities/Level.hpp"
#include "UI/UIObject.hpp"
#include "UI/MultilineText.hpp"
#include "UI/Button.hpp"

class LevelEntry : public UIObject
{
public:
	LevelEntry(const Level& level, ButtonStringCallback playButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment());
	~LevelEntry();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

private:
	void PlayButtonPressed();

	static const sf::Vector2f padding;
	static const sf::Vector2f playButtonSize;
	static const float playButtonXSpacing;
	static const float levelBottomSpacing;
	static const float stageXOffset;

	Button* playButton;
	ButtonStringCallback playButtonCallback;

	MultilineText* levelName;
	std::vector<MultilineText*> stageNames;
};