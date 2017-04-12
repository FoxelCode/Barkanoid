#include "Game/Substates/PauseSubstate.hpp"

#include "Engine/G.hpp"
#include "Engine/Input.hpp"

const float PauseSubstate::buttonSpacing = 10.0f;

PauseSubstate::PauseSubstate(sf::Vector2u size, std::function<void()> continueCallback, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback)
	: continueCallback(continueCallback), backToSelectCallback(backToSelectCallback), retryLevelCallback(retryLevelCallback)
{
	dimmer.setSize(sf::Vector2f(size));
	dimmer.setFillColor(sf::Color(0, 0, 0, 127));

	sf::Font* font = G::GetAssetManager()->GetFont("OneTrickPony.otf");

	banner.setFont(*font);
	banner.setFillColor(sf::Color::White);
	banner.setString("Paused");
	banner.setCharacterSize(64);
	banner.setPosition(size.x / 2.0f - banner.getGlobalBounds().width / 2.0f, size.y / 2.0f - 120.0f);

	float buttonYPos = size.y / 2.0f;

	Button* continueButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseSubstate::ContinueClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	continueButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	continueButton->GetText()->GetFirstLine()->setFont(*font);
	continueButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	continueButton->GetText()->GetFirstLine()->setCharacterSize(32);
	continueButton->GetText()->SetText("Continue");
	continueButton->UpdateLayout();
	Add(continueButton);
	buttonYPos += continueButton->GetSize().y + buttonSpacing;

	Button* backToSelectButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseSubstate::BackToSelectClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	backToSelectButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	backToSelectButton->GetText()->GetFirstLine()->setFont(*font);
	backToSelectButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	backToSelectButton->GetText()->GetFirstLine()->setCharacterSize(32);
	backToSelectButton->GetText()->SetText("Back to level select");
	backToSelectButton->UpdateLayout();
	Add(backToSelectButton);
	buttonYPos += backToSelectButton->GetSize().y + buttonSpacing;

	Button* retryLevelButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseSubstate::RetryLevelClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	retryLevelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	retryLevelButton->GetText()->GetFirstLine()->setFont(*font);
	retryLevelButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	retryLevelButton->GetText()->GetFirstLine()->setCharacterSize(32);
	retryLevelButton->GetText()->SetText("Retry level");
	retryLevelButton->UpdateLayout();
	Add(retryLevelButton);
}

void PauseSubstate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(dimmer, states);
	State::draw(target, states);
	target.draw(banner, states);
}

void PauseSubstate::Update(float delta)
{
	State::Update(delta);

	// These keypresses act the same as clicking the continue button
	if (Input::JustPressed(sf::Keyboard::Escape) || Input::JustPressed(sf::Keyboard::P))
		continueClicked = true;

	if (backToSelectClicked)
		backToSelectCallback();
	else if (retryLevelClicked)
		retryLevelCallback();
	else if (continueClicked)
		continueCallback();

	if (backToSelectClicked || retryLevelClicked || continueClicked)
		GetGame()->PopSubstate();
}