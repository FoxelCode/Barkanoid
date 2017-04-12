#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/State.hpp"
#include "UI/Button.hpp"

class GameOverSubstate : public State
{
public:
	GameOverSubstate(sf::Vector2u size, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback);
	~GameOverSubstate() {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void BackToSelectClicked() { backToSelectClicked = true; }
	void RetryLevelClicked() { retryLevelClicked = true; }

private:
	static const float buttonSpacing;

	std::function<void()> backToSelectCallback = nullptr;
	std::function<void()> retryLevelCallback = nullptr;
	bool backToSelectClicked = false;
	bool retryLevelClicked = false;

	sf::RectangleShape dimmer;
	sf::Text banner;
};