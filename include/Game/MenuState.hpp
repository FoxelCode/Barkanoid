#pragma once

#include "Engine/State.hpp"
#include "UI/Button.hpp"

class MenuState : public State
{
public:
	MenuState();
	~MenuState();
	void Init();

	static void StartButtonPressed();

private:
	Button* startButton = nullptr;
};