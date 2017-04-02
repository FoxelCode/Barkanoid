#include "Game/Screens/GameOverScreen.hpp"

#include "Engine/G.hpp"

const float GameOverScreen::buttonSpacing = 10.0f;

GameOverScreen::GameOverScreen(sf::Vector2u size, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback)
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

	backToSelectButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverScreen::BackToSelectClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	backToSelectButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	backToSelectButton->GetText()->GetFirstLine()->setFont(*font);
	backToSelectButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	backToSelectButton->GetText()->GetFirstLine()->setCharacterSize(32);
	backToSelectButton->GetText()->SetText("Back to level select");
	backToSelectButton->UpdateLayout();
	buttonYPos += backToSelectButton->GetSize().y + buttonSpacing;

	retryLevelButton = new Button(sf::Vector2f(size.x / 2.0f, buttonYPos), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverScreen::RetryLevelClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	retryLevelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	retryLevelButton->GetText()->GetFirstLine()->setFont(*font);
	retryLevelButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	retryLevelButton->GetText()->GetFirstLine()->setCharacterSize(32);
	retryLevelButton->GetText()->SetText("Retry level");
	retryLevelButton->UpdateLayout();
}

GameOverScreen::~GameOverScreen()
{
	if (backToSelectButton != nullptr)
	{
		delete backToSelectButton;
		backToSelectButton = nullptr;
	}
	if (retryLevelButton != nullptr)
	{
		delete retryLevelButton;
		retryLevelButton = nullptr;
	}
}

void GameOverScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dimmer, states);
	target.draw(banner, states);
	target.draw(*backToSelectButton, states);
	target.draw(*retryLevelButton, states);
}

void GameOverScreen::Update(float delta)
{
	retryLevelButton->Update(delta);
	backToSelectButton->Update(delta);

	if (backToSelectClicked)
		backToSelectCallback();
	else if (retryLevelClicked)
		retryLevelCallback();
}
