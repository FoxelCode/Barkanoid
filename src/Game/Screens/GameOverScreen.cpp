#include "Game/Screens/GameOverScreen.hpp"

#include "Engine/G.hpp"

GameOverScreen::GameOverScreen(sf::Vector2u size, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback)
	: backToSelectCallback(backToSelectCallback), retryLevelCallback(retryLevelCallback)
{
	dimmer.setSize(sf::Vector2f(size));
	dimmer.setFillColor(sf::Color(0, 0, 0, 127));

	sf::Font* font = G::GetAssetManager()->GetFont("standur.ttf");

	banner.setFont(*font);
	banner.setFillColor(sf::Color::White);
	banner.setString("Game over...");
	banner.setCharacterSize(64);
	banner.setPosition(size.x / 2.0f - banner.getGlobalBounds().width / 2.0f, size.y / 2.0f - 120.0f);

	backToSelectButton = new Button(sf::Vector2f(size.x / 2.0f, size.y / 2.0f), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverScreen::BackToSelectClicked, this));
	backToSelectButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	backToSelectButton->GetText()->setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
	backToSelectButton->GetText()->setFillColor(sf::Color::Black);
	backToSelectButton->GetText()->setString("Back to level select");
	backToSelectButton->GetText()->setCharacterSize(32);
	backToSelectButton->CenterText();

	retryLevelButton = new Button(sf::Vector2f(size.x / 2.0f, size.y / 2.0f + 40.0f), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&GameOverScreen::RetryLevelClicked, this));
	retryLevelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	retryLevelButton->GetText()->setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
	retryLevelButton->GetText()->setFillColor(sf::Color::Black);
	retryLevelButton->GetText()->setString("Retry level");
	retryLevelButton->GetText()->setCharacterSize(32);
	retryLevelButton->CenterText();
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
