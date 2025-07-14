#ifndef palette_hpp
#define palette_hpp

enum class ButtonState { Idle, Hover, Pressed };

class PaletteButton : ElementGUI {
public:
	const sf::Vector2f size = sf::Vector2f(64, 64);
	sf::Vector2f position;

	sf::RectangleShape rect;
	sf::Texture terrain_texture;
	sf::Sprite sprite;
	
	ButtonState state;
	std::function<void()> onclick_func;    
	sf::Time clickTime;

	std::string name;
	int terrain_type;
	int terrain_value;

	PaletteButton(std::string name, int terrain_type, int terrain_value) {

		this->name = name;
		this->terrain_type = terrain_type;
		this->terrain_value = terrain_value;

		rect = sf::RectangleShape(size);
		rect.setOrigin(size.x/2, size.y/2);
		rect.setPosition(position);

		terrain_texture = sf::Texture();
		terrain_texture.loadFromFile("tex\\set_0.png");

		sprite = sf::Sprite();
		sprite.setTexture(terrain_texture);
		sprite.setTextureRect(sf::IntRect(terrain_value * 15 * 64, terrain_type*64, 64, 64));
		sprite.setOrigin(32,32);
		sprite.setPosition(position);

		state = ButtonState::Idle;

		onclick_func = []() {};
		clickTime = currentTime;

	}

	void setPosition(sf::Vector2f position) {
		this->position = position;
		rect.setPosition(position);
		sprite.setPosition(position);

	}

	void unclick() {
		state = ButtonState::Idle;
		//changeColor();
	}

	void hover() {
		state = ButtonState::Hover;
		//changeColor();
	}

	void click() {
		state = ButtonState::Pressed;
		//changeColor();
		clickTime = currentTime;
	}

	void cursorHover() {
		if (rect.getGlobalBounds().contains(worldMousePosition)) {
			ElementGUI_hovered = this;
		}
		
	}

	void handleEvent(sf::Event& event) {
		if (rect.getGlobalBounds().contains(worldMousePosition)) {

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				ElementGUI_pressed = this;
			}
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				if (ElementGUI_pressed == this) {
					click();
					
				}
			}
		}

	} 

	void update(bool hover_action = true) {

		if (state == ButtonState::Pressed) {
			if ((currentTime - clickTime).asSeconds() > 0.05f) {
				if (onclick_func) {
					onclick_func();
				}
					
				ElementGUI_pressed = nullptr;
				unclick();
			}

		}
		else if (hover_action && ElementGUI_hovered == this) {
			hover();
		}
		else
			unclick();
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
	int terrain_type;
	int terrain_value;

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

		PaletteButton* btn;
		btn = new PaletteButton("sands", 0, 0);
		btn->onclick_func = [this, btn]() { 
			terrain_type = btn->terrain_type;
			terrain_value = btn->terrain_value;
			std::cout << btn->name << " - " << btn->terrain_value << "\n";
			};
		buttons.push_back(btn);

		btn = new PaletteButton("water", 0, 1);
		btn->onclick_func = [this, btn]() { 
			terrain_type = btn->terrain_type;
			terrain_value = btn->terrain_value;
			std::cout << btn->name << " - " << btn->terrain_value << "\n";
			};
		buttons.push_back(btn);

		btn = new PaletteButton("sands", 1, 0);
		btn->onclick_func = [this, btn]() {
			terrain_type = btn->terrain_type;
			terrain_value = btn->terrain_value;
			std::cout << btn->name << " - " << btn->terrain_value << "\n";
			};
		buttons.push_back(btn);

		btn = new PaletteButton("grass", 1, 1);
		btn->onclick_func = [this, btn]() {
			terrain_type = btn->terrain_type;
			terrain_value = btn->terrain_value;
			std::cout << btn->name << " - " << btn->terrain_value << "\n";
			};
		buttons.push_back(btn);

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

	void cursorHover() {
		for (auto& btn : buttons) {
			btn->cursorHover();
		}
	}

	void handleEvent(sf::Event& event) {
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (bar_rect.getGlobalBounds().contains(worldMousePosition)) {
				is_moved = true;
				offset = position - worldMousePosition;
				ElementGUI_pressed = this;
			}
		}

		if (event.type == sf::Event::MouseMoved) {
			if (is_moved == true) {
				setPosition(worldMousePosition + offset);
				ElementGUI_pressed = this;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)) {
			is_moved = false;
		}

		for (auto& btn : buttons) {
			btn->handleEvent(event);
		}
	}

	void update() {
		if (ElementGUI_pressed == this) {
			bar_rect.setPosition(position);
			rect.setPosition(position + sf::Vector2f(0, bar_size.y));
		}

		for (auto& btn : buttons)
			btn->update();
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
