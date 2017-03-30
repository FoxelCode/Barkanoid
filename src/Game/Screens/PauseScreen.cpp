#include "Game/Screens/PauseScreen.hpp"

#include "Engine/G.hpp"
#include "Engine/Input.hpp"

PauseScreen::PauseScreen(sf::Vector2u size, std::function<void()> continueCallback, std::function<void()> backToSelectCallback, std::function<void()> retryLevelCallback)
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

	continueButton = new Button(sf::Vector2f(size.x / 2.0f, size.y / 2.0f - 20.0f), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseScreen::ContinueClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	continueButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	continueButton->GetText()->setFont(*font);
	continueButton->GetText()->setFillColor(sf::Color::Black);
	continueButton->GetText()->setString("Continue");
	continueButton->GetText()->setCharacterSize(32);
	continueButton->UpdateLayout();

	backToSelectButton = new Button(sf::Vector2f(size.x / 2.0f, size.y / 2.0f + 30.0f), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseScreen::BackToSelectClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	backToSelectButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	backToSelectButton->GetText()->setFont(*font);
	backToSelectButton->GetText()->setFillColor(sf::Color::Black);
	backToSelectButton->GetText()->setString("Back to level select");
	backToSelectButton->GetText()->setCharacterSize(32);
	backToSelectButton->UpdateLayout();

	retryLevelButton = new Button(sf::Vector2f(size.x / 2.0f, size.y / 2.0f + 80.0f), sf::Vector2f(300.0f, 50.0f),
		(ButtonCallback)std::bind(&PauseScreen::RetryLevelClicked, this), Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	retryLevelButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	retryLevelButton->GetText()->setFont(*font);
	retryLevelButton->GetText()->setFillColor(sf::Color::Black);
	retryLevelButton->GetText()->setString("Retry level");
	retryLevelButton->GetText()->setCharacterSize(32);
	retryLevelButton->UpdateLayout();
}

PauseScreen::~PauseScreen()
{
	if (continueButton != nullptr)
	{
		delete continueButton;
		continueButton = nullptr;
	}
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

void PauseScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(dimmer, states);
	target.draw(banner, states);
	target.draw(*continueButton, states);
	target.draw(*backToSelectButton, states);
	target.draw(*retryLevelButton, states);
}

void PauseScreen::Update(float delta)
{
	continueButton->Update(delta);
	retryLevelButton->Update(delta);
	backToSelectButton->Update(delta);

	if (continueClicked)
		continueCallback();
	else if (backToSelectClicked)
		backToSelectCallback();
	else if (retryLevelClicked)
		retryLevelCallback();

	if (Input::JustPressed(sf::Keyboard::Escape) || Input::JustPressed(sf::Keyboard::P))
		continueCallback();
}