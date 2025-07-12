#ifndef palette_hpp
#define palette_hpp

class PaletteButton : ElementGUI {
public:
	const sf::Vector2f size = sf::Vector2f(64, 64);
	sf::Vector2f position;
	sf::Texture tex;
	sf::Sprite sprite;

	PaletteButton(std::wstring name, std::string texture) {

		tex = sf::Texture();
		tex.loadFromFile(texture);

		sprite = sf::Sprite();
		sprite.setTexture(tex);
		sprite.setScale(4, 4);
		sprite.setOrigin(tex.getSize().x/2, tex.getSize().y / 2);
		
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	void draw() {
		window->draw(sprite);
	}

};

class Palette : public ElementGUI {
public:
	sf::Vector2f bar_size;
	sf::Vector2f size;
	sf::Vector2f position;

	sf::RectangleShape bar_rect;	// top bar rect
	sf::RectangleShape rect;		// bottom big rect

	short margin = 8;

	sf::Vector2f offset;
	bool is_moved;

	std::vector < PaletteButton* > buttons;

	Palette() : ElementGUI() {
		
		sf::Vector2i tiles(2, 2);

		bar_size = sf::Vector2f(tiles.x * 64 + (tiles.x + 1) * margin, 24);
		size = sf::Vector2f(tiles.x * 64 + (tiles.x + 1) * margin, tiles.y * 64 + (tiles.y + 1) * margin);

		bar_rect = sf::RectangleShape(bar_size);
		bar_rect.setFillColor(sf::Color(32, 32, 32));
		bar_rect.setOutlineThickness(2.0f);
		bar_rect.setOutlineColor(sf::Color(32, 32, 32));

		rect = sf::RectangleShape(size);
		rect.setFillColor(sf::Color(64, 64, 64));
		rect.setOutlineThickness(2.0f);
		rect.setOutlineColor(sf::Color(32, 32, 32));

		is_moved = false;

		buttons.push_back(new PaletteButton(L"water", "tex\\water.png"));
		//buttons.push_back(new PaletteButton(L"sands", "tex\\sands.png"));
		buttons.push_back(new PaletteButton(L"grass", "tex\\grass.png"));
		//buttons.push_back(new PaletteButton(L"stone", "tex\\stone.png"));

		setPosition(sf::Vector2f(view.getSize().x - size.x - 32, 32));
	}

	
	~Palette() { }

	void setPosition(sf::Vector2f position) {
		this->position = position;

		bar_rect.setPosition(position);
		rect.setPosition(position + sf::Vector2f(0, bar_size.y));

		for (int i = 0; i < buttons.size(); i++) {
			sf::Vector2f pos;
			pos.x = buttons.front()->size.x * (0.5f + float(i % 2)) + (i%2 +1) * margin;
			pos.y = buttons.front()->size.x * (0.5f + float(i / 2)) + (i/2 +1) * margin;

			pos += position + sf::Vector2f(0, bar_size.y);

			buttons[i]->setPosition(pos);
		}
	}

	void handleEvent(sf::Event& event) {
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (bar_rect.getGlobalBounds().contains(worldMousePosition)) {
				is_moved = true;
				offset = position - worldMousePosition;
				elementGUIClicked = this;
			}
		}

		if (event.type == sf::Event::MouseMoved) {
			if (is_moved == true) {
				setPosition(worldMousePosition + offset);
				elementGUIClicked = this;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)) {
			is_moved = false;
		}
	}

	void update() {
		if (elementGUIClicked == this) {
			bar_rect.setPosition(position);
			rect.setPosition(position + sf::Vector2f(0, bar_size.y));
		}
	}

	void draw() {


		window->draw(bar_rect);
		window->draw(rect);

		for (auto& btn : buttons) {
			btn->draw();
		}
	}
};

Palette* palette = nullptr;

#endif // !map_hpp
