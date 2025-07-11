#include <iostream>

#include <SFML/Graphics.hpp>

#include "window.hpp"
#include "mouse.hpp"
#include "SFML_intro.hpp"
#include "elementGUI.hpp"
#include "palette.hpp"
#include "map.hpp"

int main() {

	SFML_intro* intro = new SFML_intro(window);
	delete intro;

	while (window->isOpen()) {

		mousePosition = sf::Mouse::getPosition(*window); // get the mouse position about window
		worldMousePosition = window->mapPixelToCoords(mousePosition); // get global mouse position
		
		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window->close();
			}
		}

		// render
		window->clear(sf::Color(48,48,48));

		window->display();


	}

	return 0;
}