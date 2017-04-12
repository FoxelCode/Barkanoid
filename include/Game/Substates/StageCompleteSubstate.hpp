#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/State.hpp"

class StageCompleteSubstate : public State
{
public:
	StageCompleteSubstate(sf::Vector2u size, std::string stageName, std::function<void()> completeCallback);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

private:
	std::function<void()> completeCallback = nullptr;

	sf::RectangleShape dimmer;
	sf::Text banner;
	sf::Text stageName;
	sf::Text continueInstructions;
};