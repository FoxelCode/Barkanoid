#include "Engine/Input.hpp"

#include <SFML/Window/Mouse.hpp>

sf::Window* Input::window = nullptr;

std::set<sf::Keyboard::Key> Input::keysJustPressed;
std::set<sf::Keyboard::Key> Input::keysPressed;
std::set<sf::Keyboard::Key> Input::keysJustReleased;

sf::Vector2i Input::mousePosition = sf::Vector2i();

void Input::SetWindow(sf::Window* window)
{
	ASSERT(Input::window == nullptr);
	Input::window = window;
}

void Input::Update()
{
	keysJustPressed.clear();
	keysJustReleased.clear();

	if (window)
	{
		mousePosition = sf::Mouse::getPosition(*window);
	}
}

void Input::HandleEvent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed)
		KeyPressed(evt.key.code);
	else if (evt.type == sf::Event::KeyReleased)
		KeyReleased(evt.key.code);
}

void Input::KeyPressed(sf::Keyboard::Key key)
{
	keysJustPressed.insert(key);
	keysPressed.insert(key);
}

void Input::KeyReleased(sf::Keyboard::Key key)
{
	keysPressed.erase(keysPressed.find(key));
	keysJustReleased.insert(key);
}

bool Input::JustPressed(sf::Keyboard::Key key)
{
	if (keysJustPressed.find(key) != keysJustPressed.end())
		return true;
	return false;
}

bool Input::Pressed(sf::Keyboard::Key key)
{
	if (keysPressed.find(key) != keysPressed.end())
		return true;
	return false;
}

bool Input::JustReleased(sf::Keyboard::Key key)
{
	if (keysJustReleased.find(key) != keysJustReleased.end())
		return true;
	return false;
}
