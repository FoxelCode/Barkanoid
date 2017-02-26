#pragma once

#include <set>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>

class Input
{
public:
	static void SetWindow(sf::Window* window);
	static void Update();
	static void HandleEvent(sf::Event evt);
	static void KeyPressed(sf::Keyboard::Key key);
	static void KeyReleased(sf::Keyboard::Key key);
	static void MouseButtonPressed(sf::Mouse::Button button);
	static void MouseButtonReleased(sf::Mouse::Button button);

	static bool JustPressed(sf::Keyboard::Key key);
	static bool Pressed(sf::Keyboard::Key key);
	static bool JustReleased(sf::Keyboard::Key key);
	static bool MouseJustPressed(sf::Mouse::Button button);
	static bool MousePressed(sf::Mouse::Button button);
	static bool MouseJustReleased(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition() { return mousePosition; }

private:
	static sf::Window* window;

	static std::set<sf::Keyboard::Key> keysJustPressed;
	static std::set<sf::Keyboard::Key> keysPressed;
	static std::set<sf::Keyboard::Key> keysJustReleased;

	static sf::Vector2i mousePosition;
	static std::set<sf::Mouse::Button> mouseJustPressed;
	static std::set<sf::Mouse::Button> mousePressed;
	static std::set<sf::Mouse::Button> mouseJustReleased;
};