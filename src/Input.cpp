#include "stdafx.h"
#include "Input.hpp"

std::set<sf::Keyboard::Key> Input::keysJustPressed;
std::set<sf::Keyboard::Key> Input::keysPressed;
std::set<sf::Keyboard::Key> Input::keysJustReleased;

void Input::Update()
{
	keysJustPressed.clear();
	keysJustReleased.clear();
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
