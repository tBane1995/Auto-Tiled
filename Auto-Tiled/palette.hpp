#ifndef palette_hpp
#define palette_hpp

class Palette : public ElementGUI {
public:
	sf::Vector2f bar_size;
	sf::Vector2f size;
	sf::Vector2f position;

	sf::RectangleShape bar_rect;	// top bar rect
	sf::RectangleShape rect;		// bottom big rect

	sf::Vector2f offset;
	bool is_moved;

	Palette() : ElementGUI() {
		short margin = 8;
		sf::Vector2i tiles(2, 2);

		bar_size = sf::Vector2f(tiles.x * 64 + (tiles.x + 1) * margin, 24);
		size = sf::Vector2f(tiles.x * 64 + (tiles.x + 1) * margin, tiles.y * 64 + (tiles.y + 1) * margin);

		position = sf::Vector2f(view.getSize().x - size.x - 32, 32);

		bar_rect = sf::RectangleShape(bar_size);
		bar_rect.setPosition(position);
		bar_rect.setFillColor(sf::Color(32, 32, 32));
		bar_rect.setOutlineThickness(2.0f);
		bar_rect.setOutlineColor(sf::Color(32, 32, 32));

		rect = sf::RectangleShape(size);
		rect.setPosition(position + sf::Vector2f(0, bar_size.y));
		rect.setFillColor(sf::Color(64, 64, 64));
		rect.setOutlineThickness(2.0f);
		rect.setOutlineColor(sf::Color(32, 32, 32));

		is_moved = false;
	}

	~Palette() { }

	void handleEvent(sf::Event& event) {
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (bar_rect.getGlobalBounds().contains(worldMousePosition)) {
				is_moved = true;
				offset = position - worldMousePosition;
			}
		}

		if (event.type == sf::Event::MouseMoved) {
			if (is_moved == true) {
				position = worldMousePosition + offset;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)) {
			is_moved = false;
		}
	}

	void update() {
		bar_rect.setPosition(position);
		rect.setPosition(position + sf::Vector2f(0, bar_size.y));
	}

	void draw() {

		

		window->draw(bar_rect);
		window->draw(rect);
	}
};

Palette* palette = nullptr;

#endif // !map_hpp
