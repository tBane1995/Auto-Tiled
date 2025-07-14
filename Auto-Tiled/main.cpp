#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

#include "window.hpp"
#include "mouse.hpp"
#include "SFML_intro.hpp"
#include "program_intro.hpp"
#include "time.hpp"
#include "elementGUI.hpp"
#include "palette.hpp"
#include "map.hpp"

int main() {

	SFML_intro* intro = new SFML_intro(window);
	delete intro;

	Program_intro* intro2 = new Program_intro(window);
	delete intro2;

	palette = new Palette();
	mapa = new Map();

	while (window->isOpen()) {
		prevTime = currentTime;
		currentTime = timeClock.getElapsedTime();

		mousePosition = sf::Mouse::getPosition(*window); // get the mouse position about window
		worldMousePosition = window->mapPixelToCoords(mousePosition); // get global mouse position
		
		ElementGUI_hovered = nullptr;
		palette->cursorHover();

		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window->close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				palette->handleEvent(event);
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				palette->handleEvent(event);

				ElementGUI_pressed = nullptr;
				
			}

			if (event.type == sf::Event::MouseMoved) {
				palette->handleEvent(event);
			}

			if (ElementGUI_pressed == nullptr) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					mapa->editTile(worldMousePosition, palette->terrain_type, palette->terrain_value);
				}
			}
		}



		// update
		palette->update();

		// render
		window->clear(sf::Color(48,48,48));
		mapa->draw();
		palette->draw();
		window->display();


	}

	return 0;
}