#include "Engine/Input.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

sf::Window* Input::window = nullptr;

std::set<sf::Keyboard::Key> Input::keysJustPressed;
std::set<sf::Keyboard::Key> Input::keysPressed;
std::set<sf::Keyboard::Key> Input::keysJustReleased;
std::set<sf::Mouse::Button> Input::mouseJustPressed;
std::set<sf::Mouse::Button> Input::mousePressed;
std::set<sf::Mouse::Button> Input::mouseJustReleased;
std::string Input::textEntered;

sf::Vector2i Input::mousePosition;
sf::Vector2i Input::mouseDelta;
float Input::mouseScrollDelta = 0.0f;
bool Input::mouseLocked = false;

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
	mouseScrollDelta = 0.0f;
	textEntered.clear();

	if (window)
	{
		sf::Vector2i newMousePosition = sf::Mouse::getPosition(*window);
		mouseDelta = newMousePosition - mousePosition;
		if (mouseLocked)
		{
			mousePosition = sf::Vector2i(window->getSize()) / 2;
			sf::Mouse::setPosition(mousePosition, *window);
		}
		else
		{
			mousePosition = newMousePosition;
		}
	}
}

void Input::HandleEvent(sf::Event evt)
{
	switch (evt.type)
	{
	case sf::Event::KeyPressed:
		EventKeyPressed(evt.key.code);
		break;
	case sf::Event::KeyReleased:
		EventKeyReleased(evt.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		EventMouseButtonPressed(evt.mouseButton.button);
		break;
	case sf::Event::MouseButtonReleased:
		EventMouseButtonReleased(evt.mouseButton.button);
		break;
	case sf::Event::TextEntered:
		EventTextEntered(evt.text.unicode);
		break;
	case sf::Event::MouseWheelScrolled:
		EventMouseScrollMoved(evt.mouseWheelScroll.delta);
		break;
	default:
		LOG_WARNING(std::to_string(evt.type) + " is not a valid event type for Input to handle");
		break;
	}
}

void Input::EventKeyPressed(sf::Keyboard::Key key)
{
	keysJustPressed.insert(key);
	keysPressed.insert(key);
}

void Input::EventKeyReleased(sf::Keyboard::Key key)
{
	auto removeIt = keysPressed.find(key);
	if (removeIt != keysPressed.end())
		keysPressed.erase(removeIt);
	keysJustReleased.insert(key);
}

void Input::EventMouseButtonPressed(sf::Mouse::Button button)
{
	mouseJustPressed.insert(button);
	mousePressed.insert(button);
}

void Input::EventMouseButtonReleased(sf::Mouse::Button button)
{
	auto removeIt = mousePressed.find(button);
	if (removeIt != mousePressed.end())
		mousePressed.erase(removeIt);
	mouseJustReleased.insert(button);
}

void Input::EventMouseScrollMoved(float delta)
{
	mouseScrollDelta = delta;
}

void Input::EventTextEntered(sf::Uint32 charCode)
{
	textEntered += (char)charCode;
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

void Input::SetMouseLocked(bool mouseLocked)
{
	Input::mouseLocked = mouseLocked;
	if (mouseLocked)
	{
		mousePosition = sf::Vector2i(window->getSize()) / 2;
		sf::Mouse::setPosition(mousePosition, *window);
	}
}
