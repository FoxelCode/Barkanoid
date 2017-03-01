#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Engine/GameObject.hpp"

class StageCompleteScreen : public GameObject
{
public:
	StageCompleteScreen(sf::Vector2u size, std::string stageName);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void SetCallback(std::function<void()> callback) { completeCallback = callback; }

private:
	std::function<void()> completeCallback = nullptr;

	sf::RectangleShape dimmer;
	sf::Text banner;
	sf::Text stageName;
	sf::Text continueInstructions;
};