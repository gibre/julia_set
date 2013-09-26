#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main()
{
	sf::Window *window;
	window = new sf::Window(sf::VideoMode(640, 480), "SFML works!");
	window->setVerticalSyncEnabled(true);

	sf::Clock clock;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			       window->close();
		}

		window->display();

		sf::Time frameTime = clock.restart();
		float fps = 1.0f / frameTime.asSeconds();
		std::cout << fps << std::endl;
	}

	delete(window);

	return 0;
}

