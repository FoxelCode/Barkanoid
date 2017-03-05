#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

#include "IUpdatable.hpp"
#include "GameObject.hpp"
#include "AssetManager.hpp"
class State;

class Game : public sf::Drawable, IUpdatable
{
public:
	Game(sf::RenderWindow& window, sf::Vector2u size, State* initialState);
	~Game();

	virtual void Update(float delta);
	void Add(GameObject* object);

	void HandleEvent(sf::Event evt);
	void SwitchState(State* newState);

	State* GetState() { return state; }
	sf::Vector2u GetSize() { return size; }
	sf::RenderWindow* GetWindow() { return window; }
	bool IsPaused() { return paused; }
	bool IsShowColliders() { return showColliders; }
	bool IsAllowStep() { return allowStep; }

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void ActuallySwitchState();

	sf::RenderWindow* window;
	const sf::Vector2u size;

	bool paused = false;
	bool showColliders = false;
	bool allowStep = false;

private:
	AssetManager asset;
	State* state = nullptr;
	State* newState = nullptr;
};