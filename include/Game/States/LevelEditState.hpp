#pragma once

#include "Engine/State.hpp"
#include "Game/Entities/Level.hpp"

class LevelEditState : public State
{
public:
	LevelEditState(std::string levelName);
	~LevelEditState();
	void Init();

private:
	static const sf::Vector2f padding;
	static const float maxHeaderHeight;
	static const float headerSpacing;

	std::string levelName;
	Level* level;
};