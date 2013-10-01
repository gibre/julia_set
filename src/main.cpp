/*
Copyright (c) 2013, Gil Brechbuhler
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the Gil Brechbuhler nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <SFML/Graphics.hpp>
#include <complex>
#include <thread>
#include <iostream>
#include "juliaset.hpp"

void fillImage(sf::Sprite *sprite_array, int _x, int _y, int partial_width, int partial_height, int width, int height, JuliaSet *set);
void handleInputs(JuliaSet *set, float frameTime);

using namespace std;

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

		handleInputs(&set, (float)clock.restart().asMilliseconds());
		window.clear();

		thread image_filler(fillImage, sprite_array, 0, 0, width/2, height/2, width, height, &set);
		thread image_filler1(fillImage, sprite_array, width/2, 0, width, height/2, width, height, &set);
		thread image_filler2(fillImage, sprite_array, 0, height/2, width/2, height, width, height, &set);
		thread image_filler3(fillImage, sprite_array, width/2, height/2, width, height, width, height, &set);
		
		image_filler.join();
		image_filler1.join();
		image_filler2.join();
		image_filler3.join();

		for (int i = 0; i < width*height; i++)
			window.draw(sprite_array[i]);
		window.display();

		//std::cout << 1.0f/clock.restart().asSeconds() << std::endl;
	}

	delete[] sprite_array;
	return 0;
}

void fillImage(sf::Sprite *sprite_array, int _x, int _y, int partial_width, int partial_height, int width, int height, JuliaSet *set)
{
	double zoom = set->getZoom();
	double moveX = set->getMoveX();
	double moveY = set->getMoveY();
	complex<double> c = set->getC();
	int max_iterations = set->getMaxIterations();
	complex<double> oldZ, newZ;
	double newRe, newIm;
	int i;

	for (int x = _x; x < partial_width; x++) {
		for (int y = _y; y < partial_height; y++) {
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
}

void handleInputs(JuliaSet *set, float frameTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		set->goLeft(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		set->goRight(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		set->goDown(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		set->goUp(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		set->increaseZoom(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		set->decreaseZoom(frameTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		set->moreIterations();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		set->lessIterations();
}
