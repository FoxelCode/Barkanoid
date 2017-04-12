#include "Game/Substates/StageCompleteSubstate.hpp"

#include "Engine/G.hpp"
#include "Engine/Input.hpp"

StageCompleteSubstate::StageCompleteSubstate(sf::Vector2u size, std::string stageName, std::function<void()> completeCallback)
	: completeCallback(completeCallback)
{
	dimmer.setSize(sf::Vector2f(size));
	dimmer.setFillColor(sf::Color(0, 0, 0, 127));

	sf::Font* font = G::GetAssetManager()->GetFont("OneTrickPony.otf");

	banner.setFont(*font);
	banner.setFillColor(sf::Color::White);
	banner.setString("Stage complete!");
	banner.setCharacterSize(64);
	banner.setPosition(size.x / 2.0f - banner.getGlobalBounds().width / 2.0f, size.y / 2.0f - 120.0f);

	this->stageName.setFont(*font);
	this->stageName.setFillColor(sf::Color::White);
	this->stageName.setString(stageName);
	this->stageName.setCharacterSize(48);
	this->stageName.setPosition(size.x / 2.0f - this->stageName.getGlobalBounds().width / 2.0f, size.y / 2.0f - 60.0f);

	continueInstructions.setFont(*font);
	continueInstructions.setFillColor(sf::Color::White);
	continueInstructions.setString("Click to continue...");
	continueInstructions.setCharacterSize(32);
	continueInstructions.setPosition(size.x / 2.0f - continueInstructions.getGlobalBounds().width / 2.0f, size.y / 2.0f);
}

void StageCompleteSubstate::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dimmer, states);
	State::draw(target, states);
	target.draw(banner, states);
	target.draw(stageName, states);
	target.draw(continueInstructions, states);
}

void StageCompleteSubstate::Update(float delta)
{
	State::Update(delta);

	if (Input::MouseJustReleased(sf::Mouse::Left))
	{
		completeCallback();
		GetGame()->PopSubstate();
	}
}
