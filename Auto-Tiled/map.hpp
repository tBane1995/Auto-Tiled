#ifndef map_hpp
#define map_hpp

class Map {
public:
	sf::Vector2f position;

	std::string data;
	sf::Vector2i size;
	std::vector < sf::Sprite > sprites;

	Map() {

		data =
			"################"
			"################"
			"##......##...###"
			"#..##.......####"
			"####.........###"
			"######....######"
			"################"
			"################";

		size = sf::Vector2i(16, 8);
		position.x = (view.getSize().x - size.x * 32) / 2;
		position.y = (view.getSize().y - size.y * 32) / 2;
		
		

		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {
				char tile = data[y*size.x + x];

				std::cout << tile;
				int index = atlasIndexAt(x, y, tile);
				//int tex_index = 0 .. 256 -> 0 .. 15
	
				sf::Texture* tex = &palette->buttons[0]->tex;

				sf::Sprite spr = sf::Sprite();
				spr.setTexture(*tex);
				spr.setScale(2, 2);
				spr.setPosition(position.x + 32 * x, position.y + 32 * y);
				sprites.push_back(spr);
				
				
			}
			std::cout << "\n";
		}

		std::cout << "\n\n";
	}

	~Map() { }

	uint8_t atlasIndexAt(uint16_t x, uint16_t y, char tile) {
		auto T = tileValueAt(x, y-1, tile);
		auto L = tileValueAt(x-1, y, tile);
		auto R = tileValueAt(x+1, y, tile);
		auto B = tileValueAt(x, y+1, tile);

		auto TL = (T == 0 || L == 0) ? 0 : tileValueAt(x - 1, y - 1, tile);
		auto TR = (T == 0 || R == 0) ? 0 : tileValueAt(x + 1, y - 1, tile);
		auto BL = (B == 0 || L == 0) ? 0 : tileValueAt(x - 1, y + 1, tile);
		auto BR = (B == 0 || R == 0) ? 0 : tileValueAt(x + 1, y + 1, tile);

		return TL * 1 + T * 2 + TR * 4 + L * 8 + R * 16 + BL * 32 + B * 64 + BR * 128;

	}

	uint8_t tileValueAt(uint16_t x, uint16_t y, char tile) {
		if (x >= size.x || y >= size.y) {
			return 1;
		}

		return data[y * size.x + x] == tile ? 1 : 0;
	}

	void draw() {
		for (auto& tile : sprites) {
			window->draw(tile);
		}
	}
};

Map* mapa = nullptr;

#endif // !map_hpp
