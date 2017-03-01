#include "Game/MenuState.hpp"

#include "Engine/Game.hpp"
#include "Engine/G.hpp"
#include "Game/PlayState.hpp"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Init()
{
	bgColour = sf::Color::Cyan;

	startButton = new Button(sf::Vector2f(GetGame()->GetSize()) / 2.0f, sf::Vector2f(200.0f, 60.0f), (ButtonCallback)std::bind(&MenuState::StartButtonPressed, this));
	startButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	startButton->GetText()->setFont(*G::GetAssetManager()->GetFont("standur.ttf"));
	startButton->GetText()->setFillColor(sf::Color::Black);
	startButton->GetText()->setString("Start Game");
	startButton->GetText()->setCharacterSize(48);
	startButton->CenterText();
	Add(startButton);
}

void MenuState::StartButtonPressed()
{
	GetGame()->SwitchState(new PlayState());
}
