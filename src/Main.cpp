#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Barkanoid Woof Woof");
	sf::RenderTexture renderTexture;

	if (!renderTexture.create(window.getSize().x, window.getSize().y))
	{
		return -1;
	}

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

		renderTexture.clear();
		renderTexture.draw(*game);
		renderTexture.display();

		const sf::Texture& t = renderTexture.getTexture();
		const sf::Sprite s(t);

		window.clear();
		window.draw(s);
		window.display();
	}

	return 0;
}