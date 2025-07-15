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
#include "camera.hpp"
#include "elementGUI.hpp"
#include "palette.hpp"
#include "map.hpp"

int main() {

	SFML_intro* intro = new SFML_intro(window);
	delete intro;

	Program_intro* intro2 = new Program_intro(window);
	delete intro2;

	cam = new Camera();
	window->setView(cam->view);

	palette = new Palette();
	mapa = new Map();

	while (window->isOpen()) {
		prevTime = currentTime;
		currentTime = timeClock.getElapsedTime();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			float dt = currentTime.asSeconds() - prevTime.asSeconds();
			float moveSpeed = 300.0f * dt;
			cam->move(0.0f, -moveSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			float dt = currentTime.asSeconds() - prevTime.asSeconds();
			float moveSpeed = 300.0f * dt;
			cam->move(-moveSpeed, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			float dt = currentTime.asSeconds() - prevTime.asSeconds();
			float moveSpeed = 300.0f * dt;
			cam->move(0.0f, moveSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			float dt = currentTime.asSeconds() - prevTime.asSeconds();
			float moveSpeed = 300.0f * dt;
			cam->move(moveSpeed, 0.0f);
		}

		cam->update();
		window->setView(cam->view);

		mousePosition = sf::Mouse::getPosition(*window); // get the mouse position about window
		worldMousePosition = window->mapPixelToCoords(mousePosition); // get global mouse position
		
		// cursor hovering
		ElementGUI_hovered = nullptr;
		palette->cursorHover();

		// Element GUI update before handle events
		palette->update();
		
		// handle events
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
		// ..
		// ..
		// ..

		// render
		window->clear(sf::Color(48,48,48));
		mapa->draw();
		palette->draw();
		window->display();


	}

	return 0;
}