#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/State.hpp"
#include "UI/Button.hpp"

class PauseSubstate : public State
{
public:
	PauseSubstate(sf::Vector2u size, std::function<void()> continueCallback, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback);
	~PauseSubstate() {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void ContinueClicked() { continueClicked = true; }
	void BackToSelectClicked() { backToSelectClicked = true; }
	void RetryLevelClicked() { retryLevelClicked = true; }

private:
	static const float buttonSpacing;

	std::function<void()> continueCallback = nullptr;
	std::function<void()> backToSelectCallback = nullptr;
	std::function<void()> retryLevelCallback = nullptr;
	bool continueClicked = false;
	bool backToSelectClicked = false;
	bool retryLevelClicked = false;

	sf::RectangleShape dimmer;
	sf::Text banner;
};