#ifndef map_hpp
#define map_hpp

class Map {
public:
	sf::Vector2f position;

	std::string data;
	sf::Vector2i size;
	std::vector < sf::Sprite > sprites;
	std::vector < sf::Texture > textures;

	Map() {

		
		data =
			"..##"
			"..##"
			"..##"
			"..##";

		size = sf::Vector2i(4, 4);

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

		data =
			"................"
			"..###......##..."
			".#####...#####.."
			".##############."
			"...###########.."
			"..##..#######..."
			"..#.....###....."
			"................";

		size = sf::Vector2i(16, 8);
		
		position.x = (view.getSize().x - size.x * 32) / 2;
		position.y = (view.getSize().y - size.y * 32) / 2;
		
		for (int i = 0; i < 16; i++) {
			sf::Texture t;
			t.loadFromFile("tex\\" + std::to_string(i) + ".png");
			textures.push_back(t);
		}

		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {
				std::cout << data[y*size.x + x];
			}
			std::cout << "\n";
		}
		std::cout << "\n";

		
		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {

				char tile = data[y*size.x + x];
				int index = getTileIndex(x, y, tile);

				sf::Sprite spr = sf::Sprite();
				spr.setTexture(textures[index]);
				spr.setScale(0.5f, 0.5f);
				spr.setPosition(position.x + 32 * x, position.y + 32 * y);
				sprites.push_back(spr);
				
				
			}
			
		}

		
	}

	~Map() { }

	int getTileIndex(int x, int y, char tile) {

		int index;
		
		if (tile == '#')
			index = 15;
		else {
			index = 0;
			if (getTileValue(x, y - 1)) index = index | 3;		// (3-ci png)
			if (getTileValue(x - 1, y)) index = index | 5;		// (5-ty png)
			if (getTileValue(x + 1, y)) index = index | 10;	// (10-ty png)
			if (getTileValue(x, y + 1)) index = index | 12;	// (12-sty png)

			if (getTileValue(x - 1, y - 1)) index = index | 1;	// (1-szy png)
			if (getTileValue(x + 1, y - 1)) index = index | 2;	// (2-gi png)
			if (getTileValue(x - 1, y + 1)) index = index | 4;	// (4-ty png)
			if (getTileValue(x + 1, y + 1)) index = index | 8;	// (8-my png)

		}
		
		//std::cout << x << ", " << y << " : " << index << "\n";

		return index;
	}

	int getTileValue(int x, int y) {
		if (x >= size.x || y >= size.y || x < 0 || y < 0) {
			return 0;
		}

		return data[y * size.x + x] == '#' ? 1 : 0;
	}

	void draw() {
		for (auto& tile : sprites) {
			window->draw(tile);
		}

	}
};

Map* mapa = nullptr;

#endif // !map_hpp
