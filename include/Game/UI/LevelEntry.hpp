#pragma once

#include "Game/Entities/Level.hpp"
#include "UI/UIObject.hpp"
#include "UI/MultilineText.hpp"
#include "UI/Button.hpp"

class LevelEntry : public UIObject
{
public:
	LevelEntry(const Level& level, ButtonStringCallback playButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment(), ButtonStringCallback editButtonCallback = nullptr);
	~LevelEntry();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

private:
	void PlayButtonPressed();
	void EditButtonPressed();

	static const sf::Vector2f padding;
	static const float levelBottomSpacing;
	static const float stageScoreWidth;
	static const float stageScoreXSpacing;

	Button* playButton;
	Button* editButton;
	ButtonStringCallback playButtonCallback;
	ButtonStringCallback editButtonCallback;

	MultilineText* levelName;
	MultilineText* levelScore;
	std::vector<MultilineText*> stageNames;
	std::vector<MultilineText*> stageScores;
};