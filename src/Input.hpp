#pragma once

#include <set>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>

class Input
{
public:
	static void Update();
	static void HandleEvent(sf::Event evt);
	static void KeyPressed(sf::Keyboard::Key key);
	static void KeyReleased(sf::Keyboard::Key key);

	static bool JustPressed(sf::Keyboard::Key key);
	static bool Pressed(sf::Keyboard::Key key);
	static bool JustReleased(sf::Keyboard::Key key);

private:
	static std::set<sf::Keyboard::Key> keysJustPressed;
	static std::set<sf::Keyboard::Key> keysPressed;
	static std::set<sf::Keyboard::Key> keysJustReleased;
};