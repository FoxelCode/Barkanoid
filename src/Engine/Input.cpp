#include "Engine/Input.hpp"

#include <SFML/Window/Mouse.hpp>

sf::Window* Input::window = nullptr;

std::set<sf::Keyboard::Key> Input::keysJustPressed;
std::set<sf::Keyboard::Key> Input::keysPressed;
std::set<sf::Keyboard::Key> Input::keysJustReleased;
std::set<sf::Mouse::Button> Input::mouseJustPressed;
std::set<sf::Mouse::Button> Input::mousePressed;
std::set<sf::Mouse::Button> Input::mouseJustReleased;

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
	mouseJustPressed.clear();
	mouseJustReleased.clear();

	if (window)
	{
		mousePosition = sf::Mouse::getPosition(*window);
	}
}

void Input::HandleEvent(sf::Event evt)
{
	switch (evt.type)
	{
	case sf::Event::KeyPressed:
		KeyPressed(evt.key.code);
		break;
	case sf::Event::KeyReleased:
		KeyReleased(evt.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		MouseButtonPressed(evt.mouseButton.button);
		break;
	case sf::Event::MouseButtonReleased:
		MouseButtonReleased(evt.mouseButton.button);
		break;
	}
}

void Input::KeyPressed(sf::Keyboard::Key key)
{
	keysJustPressed.insert(key);
	keysPressed.insert(key);
}

void Input::KeyReleased(sf::Keyboard::Key key)
{
	auto removeIt = keysPressed.find(key);
	if (removeIt != keysPressed.end())
		keysPressed.erase(removeIt);
	keysJustReleased.insert(key);
}

void Input::MouseButtonPressed(sf::Mouse::Button button)
{
	mouseJustPressed.insert(button);
	mousePressed.insert(button);
}

void Input::MouseButtonReleased(sf::Mouse::Button button)
{
	auto removeIt = mousePressed.find(button);
	if (removeIt != mousePressed.end())
		mousePressed.erase(removeIt);
	mouseJustReleased.insert(button);
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

bool Input::MouseJustPressed(sf::Mouse::Button button)
{
	if (mouseJustPressed.find(button) != mouseJustPressed.end())
		return true;
	return false;
}

bool Input::MousePressed(sf::Mouse::Button button)
{
	if (mousePressed.find(button) != mousePressed.end())
		return true;
	return false;
}

bool Input::MouseJustReleased(sf::Mouse::Button button)
{
	if (mouseJustReleased.find(button) != mouseJustReleased.end())
		return true;
	return false;
}
