#include "Engine/Game.hpp"

#include "Util/Math.hpp"
#include "Util/Random.hpp"
#include "Collision/Collision.hpp"
#include "Engine/G.hpp"
#include "Game/Palette.hpp"
#include "Engine/Input.hpp"
#include "Engine/State.hpp"
#include "Util/Tween.hpp"

#include <vector>
#include <cfloat>
#include <iostream>

#include <SFML\Window\Event.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

Game::Game(sf::RenderWindow& window, sf::Vector2u size, State* initialState, const float delta)
	: window(&window), size(size)
{
	G::SetGame(this);
	G::SetAssetManager(&asset);
	Input::SetWindow(&window);
	Random::Seed();
	Collision::SetDelta(delta);

	window.setKeyRepeatEnabled(false);

	ASSERT(initialState != nullptr);
	state = initialState;
	state->SetGame(this);
	state->Init();
}

Game::~Game()
{
	if (state != nullptr)
	{
		delete state;
		state = nullptr;
	}
}

void Game::Update(float delta)
{
	allowStep = false;

#ifndef _NDEBUG
	if (Input::JustPressed(sf::Keyboard::Num1))
		paused = !paused;
	if (Input::JustPressed(sf::Keyboard::Num3))
		showColliders = !showColliders;

	if (paused && Input::JustPressed(sf::Keyboard::Num2))
		allowStep = true;
#endif

	if (!paused || allowStep)
		state->Update(delta);

	Tween::UpdateTweens(delta);
	Input::Update();

	if (newState != nullptr)
		ActuallySwitchState();
}

void Game::HandleEvent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed || evt.type == sf::Event::KeyReleased
		|| evt.type == sf::Event::MouseButtonPressed || evt.type == sf::Event::MouseButtonReleased)
		Input::HandleEvent(evt);
}

void Game::SwitchState(State* newState)
{
	ASSERT(newState != nullptr);
	this->newState = newState;
	Tween::StopAll();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	state->draw(target, states);
}

void Game::ActuallySwitchState()
{
	if (state != nullptr)
		delete state;
	state = newState;
	newState = nullptr;
	state->SetGame(this);
	state->Init();
}
