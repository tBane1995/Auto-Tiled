#ifndef map_hpp
#define map_hpp

class Map {
public:
	sf::Vector2f position;

	std::string data;
	sf::Vector2i size;
	std::vector < sf::Sprite > sprites;
	sf::Texture tileset;

	Map() {

		data =
			"........................"
			"........................"
			"........................"
			"......###......##......."
			".....#####...#####......"
			".....##############....."
			".......###########......"
			"......##..#######......."
			"......#.....###........."
			"........................"
			"........................"
			"........................";

		size = sf::Vector2i(24, 12);

		
		position.x = (view.getSize().x - size.x * 32) / 2;
		position.y = (view.getSize().y - size.y * 32) / 2;
		
		tileset = sf::Texture();
		tileset.loadFromFile("tex\\00_set.png");

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
				int index = getTileIndex(x, y);

				sf::Sprite spr = sf::Sprite();
				spr.setTexture(tileset);
				spr.setTextureRect(sf::IntRect(index * 64, 0, 64, 64));
				spr.setScale(0.5f, 0.5f);
				spr.setPosition(position.x + x*32, position.y + y*32);
				sprites.push_back(spr);
				
			}
		}
	}

	~Map() { }


	int getTileIndex(int x, int y) {
		return getTileValue(x,y) | (getTileValue(x+1,y) << 1) | (getTileValue(x,y+1) << 2) | (getTileValue(x+1, y+1) << 3);
	}

	int getTileValue(int x, int y) {
		if (x >= size.x || y >= size.y || x < 0 || y < 0) {
			return 1;
		}

		return data[y * size.x + x] == '#' ? 0 : 1;
	}

	void editTile(int x, int y, TerrainType terrain_type) {

		if (terrain_type == TerrainType::Water)
			data[y * size.x + x] = '.';
		else
			data[y * size.x + x] = '#';

		for (int yy = y - 1; yy <= y + 1; yy++) {
			for (int xx = x - 1; xx <= x + 1; xx++) {

				if (xx >= size.x || yy >= size.y || xx < 0 || yy < 0)
					continue;

				int index = getTileIndex(xx, yy);
				sprites[yy*size.x+xx].setTextureRect(sf::IntRect(index * 64, 0, 64, 64));
			}
		}
	}

	void editTile(sf::Vector2f mopusePosition, TerrainType terrain_type) {

		int x = (worldMousePosition.x + 16 - position.x) / 32;
		int y = (worldMousePosition.y + 16 - position.y) / 32;

		if (terrain_type == TerrainType::Water)
			data[y * size.x + x] = '.';
		else
			data[y * size.x + x] = '#';

		for (int yy = y - 1; yy <= y + 1; yy++) {
			for (int xx = x - 1; xx <= x + 1; xx++) {

				if (xx >= size.x || yy >= size.y || xx < 0 || yy < 0)
					continue;

				int index = getTileIndex(xx, yy);
				sprites[yy * size.x + xx].setTextureRect(sf::IntRect(index * 64, 0, 64, 64));
			}
		}
	}

	void draw() {
		for (auto& tile : sprites) {
			window->draw(tile);
		}

	}
};

Map* mapa = nullptr;

#endif // !map_hpp
