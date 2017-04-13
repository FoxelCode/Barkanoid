#pragma once

#include "Engine/State.hpp"
#include "Engine/Game.hpp"
#include "Game/Entities/GameArea.hpp"
#include "Game/Entities/Level.hpp"
#include "Game/Entities/Stage.hpp"

class StageEditState : public State
{
public:
	StageEditState(std::string levelName);
	~StageEditState();

	void Init();
	void Update(float delta);

private:
	GameArea* gameArea = nullptr;
	std::string levelName;
	Level* level = nullptr;
	Stage* stage = nullptr;
};