#include "Game/States/MenuState.hpp"

#include "Engine/Game.hpp"
#include "Engine/G.hpp"
#include "Engine/Input.hpp"
#include "Game/States/LevelSelectState.hpp"
#include "Util/Tween.hpp"
#include "UI/TextField.hpp"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Init()
{
	bgColour = sf::Color::Cyan;

	startButton = new Button(sf::Vector2f(GetGame()->GetSize()) / 2.0f, sf::Vector2f(240.0f, 60.0f), (ButtonCallback)std::bind(&MenuState::StartButtonPressed, this),
		Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
	startButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	startButton->GetText()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	startButton->GetText()->setFillColor(sf::Color::Black);
	startButton->GetText()->setString("Start Game");
	startButton->GetText()->setCharacterSize(48);
	startButton->UpdateLayout();
	Add(startButton);

	Tween::Start(Ease::Type::QuartOut, -startButton->GetCollider()->GetBounds().width / 2.0f, GetGame()->GetSize().x / 2.0f, 1.0f,
		[this](float v) { startButton->SetPosition(v, startButton->GetPosition().y); } );
}

void MenuState::StartButtonPressed()
{
	GetGame()->SwitchState(new LevelSelectState());
}
