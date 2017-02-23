#include <vld.h>

#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Game/Barkanoid.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 640), "Barkanoid Woof Woof");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Clock deltaClock;
	const float deltaTime = 1.0f / 100.0f;
	float deltaAccumulator = 0.0f;

	Barkanoid* game = new Barkanoid(window, sf::Vector2u(480, 640));

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

	delete game;

	return 0;
}