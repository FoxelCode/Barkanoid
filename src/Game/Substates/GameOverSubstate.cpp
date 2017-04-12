#include "Game/Substates/GameOverSubstate.hpp"

#include "Engine/G.hpp"

const float GameOverSubstate::buttonSpacing = 10.0f;

GameOverSubstate::GameOverSubstate(sf::Vector2u size, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback)
	: backToSelectCallback(backToSelectCallback), retryLevelCallback(retryLevelCallback)
{
	dimmer.setSize(sf::Vector2f(size));
	dimmer.setFillColor(sf::Color(0, 0, 0, 127));

	sf::Font* font = G::GetAssetManager()->GetFont("OneTrickPony.otf");

	banner.setFont(*font);
	banner.setFillColor(sf::Color::White);
	banner.setString("Game over...");
	banner.setCharacterSize(64);
	banner.setPosition(size.x / 2.0f - banner.getGlobalBounds().width / 2.0f, size.y / 2.0f - 120.0f);

	float buttonYPos = size.y / 2.0f;

	Button* backToSelectButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverSubstate::BackToSelectClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	backToSelectButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	backToSelectButton->GetText()->GetFirstLine()->setFont(*font);
	backToSelectButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	backToSelectButton->GetText()->GetFirstLine()->setCharacterSize(32);
	backToSelectButton->GetText()->SetText("Back to level select");
	backToSelectButton->UpdateLayout();
	Add(backToSelectButton);
	buttonYPos += backToSelectButton->GetSize().y + buttonSpacing;

	Button* retryLevelButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverSubstate::RetryLevelClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	retryLevelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	retryLevelButton->GetText()->GetFirstLine()->setFont(*font);
	retryLevelButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	retryLevelButton->GetText()->GetFirstLine()->setCharacterSize(32);
	retryLevelButton->GetText()->SetText("Retry level");
	retryLevelButton->UpdateLayout();
	Add(retryLevelButton);
}

void GameOverSubstate::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dimmer, states);
	State::draw(target, states);
	target.draw(banner, states);
}

void GameOverSubstate::Update(float delta)
{
	State::Update(delta);

	if (backToSelectClicked)
		backToSelectCallback();
	else if (retryLevelClicked)
		retryLevelCallback();

	if (backToSelectClicked || retryLevelClicked)
		GetGame()->PopSubstate();
}
