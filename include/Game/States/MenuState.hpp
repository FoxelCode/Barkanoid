#pragma once

#include "Engine/State.hpp"
#include "UI/Button.hpp"

class MenuState : public State
{
public:
	MenuState();
	~MenuState();
	void Init();

	void StartButtonPressed();
	void EditButtonPressed();

private:
	Button* startButton = nullptr;
	Button* editButton = nullptr;
};