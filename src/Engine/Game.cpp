#include "Engine/Game.hpp"

#include "Util/Math.hpp"
#include "Util/Random.hpp"
#include "Collision/Collision.hpp"
#include "Engine/G.hpp"
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
	G::SetAudioManager(&audio);

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
	Tween::StopAll();
}

void Game::Update(float delta)
{
	allowStep = false;

#ifndef NDEBUG
	if (Input::JustPressed(sf::Keyboard::Num1))
		paused = !paused;
	if (Input::JustPressed(sf::Keyboard::Num3))
		showColliders = !showColliders;

	if (paused && Input::JustPressed(sf::Keyboard::Num2))
		allowStep = true;
#endif

	if (Input::JustPressed(sf::Keyboard::M))
		audio.ToggleMute();

	if (!paused || allowStep)
	{
		if (!substates.empty())
			(*substates.rbegin())->Update(delta);
		else
			state->Update(delta);
		Tween::UpdateTweens(delta);
	}

	state->PostUpdate();
	Input::Update();

	if (newState != nullptr)
		ActuallySwitchState();
}

void Game::HandleEvent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed || evt.type == sf::Event::KeyReleased
		|| evt.type == sf::Event::MouseButtonPressed || evt.type == sf::Event::MouseButtonReleased
		|| evt.type == sf::Event::TextEntered || evt.type == sf::Event::MouseWheelScrolled)
		Input::HandleEvent(evt);
}

void Game::SwitchState(State* newState)
{
	ASSERT(newState != nullptr);
	this->newState = newState;
}

void Game::AddSubstate(State* newSubstate)
{
	ASSERT(newSubstate != nullptr);
	substates.push_back(newSubstate);
	newSubstate->SetGame(this);
}

void Game::PopSubstate()
{
	ASSERT(!substates.empty());
	State* topSubstate = (*substates.rbegin());
	if (topSubstate != nullptr)
		delete topSubstate;
	substates.pop_back();
}

void Game::ClearSubstates()
{
	for (State* substate : substates)
		if (substate != nullptr)
			delete substate;
	substates.clear();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(state->GetBGColour());
	state->draw(target, states);
	for (const State* substate : substates)
		substate->draw(target, states);
}

void Game::ActuallySwitchState()
{
	if (state != nullptr)
		delete state;
	if (!substates.empty())
		ClearSubstates();
	Tween::StopAll();
	state = newState;
	newState = nullptr;
	state->SetGame(this);
	state->Init();
}
