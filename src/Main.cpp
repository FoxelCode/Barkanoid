#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Barkanoid Woof Woof");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Clock deltaClock;
	const float deltaTime = 0.01f;
	float deltaAccumulator = 0.0f;

	Game* game = new Game(window, sf::Vector2u(600, 800));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float delta = deltaClock.restart().asSeconds();
		deltaAccumulator += delta;

		while (deltaAccumulator >= deltaTime)
		{
			game->Update(deltaTime);
			deltaAccumulator -= deltaTime;
		}

		window.clear();
		window.draw(*game);
		window.display();
	}

	return 0;
}