#ifndef program_intro_hpp
#define program_intro_hpp

enum class Program_intro_states { start, logo_entry_anim, logo_hidding, end };

class Program_intro {

public:
	Program_intro_states state;

	sf::Texture logo_texture;
	sf::Sprite logo_sprite;
	
	sf::Font font;
	sf::Text text;

	sf::Time start_time;

	Program_intro(sf::RenderWindow* window) {

		logo_texture = sf::Texture();
		logo_texture.loadFromFile("tex\\logo.png");

		logo_sprite = sf::Sprite();
		logo_sprite.setTexture(logo_texture);

		sf::Vector2f screen_size = sf::Vector2f(window->getSize().x, window->getSize().y);
		float logo_scale;
		if (window->getSize().x < window->getSize().y) {
			// Skaluj względem szerokości okna
			logo_scale = (window->getSize().x * 0.4f) / float(logo_texture.getSize().x);
		}
		else {
			// Skaluj względem wysokości okna
			logo_scale = (window->getSize().y * 0.4f) / float(logo_texture.getSize().y);
		}
		logo_sprite.setScale(logo_scale, logo_scale);
		logo_sprite.setOrigin(logo_texture.getSize().x/2, logo_texture.getSize().y/ 2);

		font = sf::Font();
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
		text = sf::Text(L"Auto-Tiled", font, 48);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height/2);
		text.setScale(logo_scale, logo_scale);
		text.setFillColor(sf::Color::White);
		play(window);
	}

	~Program_intro() { }

	void play(sf::RenderWindow* window) {
		state = Program_intro_states::start;
		sf::Clock clock;
		start_time = clock.getElapsedTime();

		float center_x = window->getSize().x / 2.0f;
		float center_y = window->getSize().y / 2.0f;

		float logo_h = logo_sprite.getGlobalBounds().height;
		float text_h = text.getGlobalBounds().height;
		float total_h = logo_h + text_h;
		float offset_y = center_y - total_h / 2.0f - 48.0f;

		// ustaw pozycje
		logo_sprite.setPosition(center_x, offset_y + logo_h/2.0f);
		text.setPosition(center_x, offset_y + logo_h + text_h / 2.0f);

		window->clear(sf::Color::Black);
		window->display();

		state = Program_intro_states::logo_entry_anim;

		while (state != Program_intro_states::end) {

			if (state == Program_intro_states::logo_entry_anim) {
				float col_alpha = (clock.getElapsedTime() - start_time).asSeconds() * 50000.0f / 255.0f;
				
				logo_sprite.setColor(sf::Color(255.0f, 255.0f, 255.0f, col_alpha));
				text.setColor(sf::Color(255.0f, 255.0f, 255.0f, col_alpha));

				window->clear(sf::Color::Black);
				window->draw(logo_sprite);
				window->draw(text);
				window->display();

				if (col_alpha > 255) {
					state = Program_intro_states::logo_hidding;
					start_time = clock.getElapsedTime();
				}
			}
			else if (state == Program_intro_states::logo_hidding) {
				float col_alpha = 255 - (clock.getElapsedTime() - start_time).asSeconds() * 100000.0f / 255.0f;
				logo_sprite.setColor(sf::Color(255.0f, 255.0f, 255.0f, col_alpha));
				text.setColor(sf::Color(255.0f, 255.0f, 255.0f, col_alpha));
				window->clear(sf::Color::Black);
				window->draw(logo_sprite);
				window->draw(text);
				window->display();

				if (col_alpha <= 0) {
					state = Program_intro_states::end;
				}
			}
		}
	}

};
#endif // !program_intro_hpp
