#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Barkanoid Woof Woof");
	sf::Clock deltaClock;
	Game* game = new Game(window, sf::Vector2u(600, 800));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time deltaTime = deltaClock.restart();
		game->Update(deltaTime.asSeconds());

		window.clear();
		window.draw(*game);
		window.display();
	}

	return 0;
}