#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Game.hpp"

void renderThread(sf::RenderWindow* window, Game* game)
{
	while (window->isOpen())
	{
		window->clear();
		window->draw(*game);
		window->display();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Barkanoid Woof Woof");
	window.setVerticalSyncEnabled(true);
	window.setActive(false);
	sf::Clock deltaClock;
	Game* game = new Game(window, sf::Vector2u(600, 800));
	std::thread render(renderThread, &window, game);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float delta = deltaClock.restart().asSeconds();
		game->Update(delta);
		if (delta > 0.02f)
			std::cout << "STUTTER: " << delta << std::endl;
	}

	render.join();

	return 0;
}