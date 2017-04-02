#ifndef NDEBUG
#include <vld.h>
#endif

#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Game/Barkanoid.hpp"
#include "Game/States/MenuState.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 640), "Barkanoid Woof Woof");

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Clock deltaClock;
	const float deltaTime = 1.0f / 100.0f;
	const float maxDeltaAccumulator = deltaTime * 2.0f;
	float deltaAccumulator = 0.0f;

	MenuState* initialState = new MenuState();
	Barkanoid game(window, sf::Vector2u(480, 640), initialState, deltaTime);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
				game.HandleEvent(event);
		}

		float delta = deltaClock.restart().asSeconds();
		deltaAccumulator += delta;
		if (deltaAccumulator > maxDeltaAccumulator)
			deltaAccumulator = maxDeltaAccumulator;

		while (deltaAccumulator >= deltaTime)
		{
			game.Update(deltaTime);
			deltaAccumulator -= deltaTime;
		}

		window.draw(game);
		window.display();
	}

	return 0;
}