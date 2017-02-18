#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 640), "Barkanoid Woof Woof");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Clock deltaClock;
	const float deltaTime = 0.01f;
	float deltaAccumulator = 0.0f;
	sf::Color clearColour = sf::Color::Black;

	Game* game = new Game(window, sf::Vector2u(480, 640));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
				game->HandleEvent(event);
		}

		float delta = deltaClock.restart().asSeconds();
		deltaAccumulator += delta;

		while (deltaAccumulator >= deltaTime)
		{
			game->Update(deltaTime);
			deltaAccumulator -= deltaTime;
		}

		window.draw(*game);
		window.display();
	}

	return 0;
}