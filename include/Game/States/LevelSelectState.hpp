#pragma once

#include "Engine/State.hpp"
#include "UI/Button.hpp"

class LevelSelectState : public State
{
public:
	LevelSelectState() {}
	void Init();
	
private:
	void LevelButtonPressed(std::string buttonText);

	static const float buttonHeight;
	static const float buttonSpacing;
	static const float editButtonWidth;

	std::vector<std::pair<std::string, std::string>> levelDatas;
};