#include <SFML/Graphics.hpp>
#include <complex>
#include <thread>
#include <mutex>
#include <iostream>
#include "juliaset.hpp"

void fillImage(sf::Sprite *sprite_array, int width, int height, JuliaSet *set);
void handleInputs(JuliaSet *set);

using namespace std;

mutex image_mutex;
sf::Texture color;

int main()
{
	int width = 200;
	int height = 200;
	JuliaSet set;
	sf::Sprite *sprite_array = new sf::Sprite[width*height];
	color.loadFromFile("../textures/palette.png");

	// création de la fenêtre
	sf::RenderWindow window(sf::VideoMode(width, height), "My window");
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen())
	{
		// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::Resized) {
				width = event.size.width;
				height = event.size.height;

				delete[] sprite_array;
				sprite_array = new sf::Sprite[width*height];
			}
		}

		handleInputs(&set);
		window.clear();

		thread image_filler(fillImage, sprite_array, width, height, &set);
		image_filler.join();

		image_mutex.lock();
		for (int i = 0; i < width*height; i++)
			window.draw(sprite_array[i]);
		window.display();
		image_mutex.unlock();

		std::cout << 1.0f/clock.restart().asSeconds() << std::endl;
	}

	delete[] sprite_array;
	return 0;
}

void fillImage(sf::Sprite *sprite_array, int width, int height, JuliaSet *set)
{
	double zoom = set->getZoom();
	double moveX = set->getMoveX();
	double moveY = set->getMoveY();
	complex<double> c = set->getC();
	int max_iterations = set->getMaxIterations();
	complex<double> oldZ, newZ;
	double newRe, newIm;
	int i;

	image_mutex.lock();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			newRe = 1.5 * (x - (width / 2)) / (0.5 * zoom * width) + moveX;
			newIm = (y - height / 2) / (0.5 * zoom * height) + moveY;
			newZ = complex<double> (newRe, newIm);

			for (i = 0; i < max_iterations; i++) {
				oldZ = newZ;

				newZ = oldZ*oldZ + c;

				if((newZ.real() * newZ.real() + newZ.imag() * newZ.imag()) > 4)
					break;
			}

			sprite_array[x + y*width].setTexture(color);
			if (i == max_iterations)
				sprite_array[x + y*width].setTextureRect(sf::IntRect(0, 0, 1, 1));
			else
				sprite_array[x + y*width].setTextureRect(sf::IntRect((i % 255)+1, 0, 1, 1));

			sprite_array[x + y*width].setPosition(x, y);
		}
	}
	image_mutex.unlock();
}

void handleInputs(JuliaSet *set)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		set->goLeft();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		set->goRight();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		set->goDown();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		set->goUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		set->increaseZoom();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		set->decreaseZoom();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		set->moreIterations();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		set->lessIterations();
}
