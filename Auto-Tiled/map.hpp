#ifndef map_hpp
#define map_hpp

sf::Vector2f tile_size = sf::Vector2f(32, 32);

class Map {
public:
	sf::Vector2f position;

	std::vector < int > terrain_types;
	std::vector < int > terrain_values;

	sf::Vector2i size;
	std::vector < sf::Sprite > sprites;
	sf::Texture tileset;

	Map() {

		
		size = sf::Vector2i(24, 12);

		for (int y = 0; y <= size.y; y++) {
			for (int x = 0; x <= size.x; x++) {
				terrain_types.push_back(int(0));
				terrain_values.push_back(int(1));
			}
		}
		
		position.x = 0;
		position.y = 0;
		
		tileset = sf::Texture();
		tileset.loadFromFile("tex\\set_0.png");

		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {
				std::cout << terrain_values[y*size.x + x];
			}
			std::cout << "\n";
		}
		std::cout << "\n";

		
		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {

				int index = getTileIndex(x, y);

				sf::Sprite spr = sf::Sprite();
				spr.setTexture(tileset);
				spr.setTextureRect(sf::IntRect(index * 64, terrain_types[y*size.x+x]*64, 64, 64));
				spr.setScale(tile_size.x/32.0f*0.5f, tile_size.y/32.0f*0.5f);
				spr.setPosition(position.x + x * tile_size.x, position.y + y * tile_size.y);
				sprites.push_back(spr);
				
			}
		}
	}

	~Map() { }


	int getTileIndex(int x, int y) {
		int ttype = terrain_types[y * size.x + x];
		return getTileValue(x,y, ttype) | (getTileValue(x+1,y,ttype) << 1) | (getTileValue(x,y+1,ttype) << 2) | (getTileValue(x+1, y+1,ttype) << 3);
	}

	int getTileValue(int x, int y, int terrain_type) {
		
		return (terrain_type == terrain_types[y * size.x + x]) ? terrain_values[y * size.x + x] : 0;
		 
	}

	void editTile(int x, int y, int terrain_type, int terrain_value) {

		terrain_types[y * size.x + x] = terrain_type;
		terrain_values[y * size.x + x] = terrain_value;

		for (int yy = y - 1; yy <= y + 1; yy++) {
			for (int xx = x - 1; xx <= x + 1; xx++) {

				if (xx >= size.x || yy >= size.y || xx < 0 || yy < 0)
					continue;

				int index = getTileIndex(xx, yy);
				sprites[yy*size.x+xx].setTextureRect(sf::IntRect(index * 64, terrain_types[yy * size.x + xx] * 64, 64, 64));
			}
		}
	}

	void editTile(sf::Vector2f mopusePosition, int terrain_type, int terrain_value) {

		int x = (worldMousePosition.x + 16 - position.x) / tile_size.x;
		int y = (worldMousePosition.y + 16 - position.y) / tile_size.y;

		terrain_types[y * size.x + x] = terrain_type;
		terrain_values[y * size.x + x] = terrain_value;

		for (int yy = y - 1; yy <= y + 1; yy++) {
			for (int xx = x - 1; xx <= x + 1; xx++) {

				if (xx >= size.x || yy >= size.y || xx < 0 || yy < 0)
					continue;

				int index = getTileIndex(xx, yy);
				sprites[yy * size.x + xx].setTextureRect(sf::IntRect(index * 64, terrain_types[yy * size.x + xx] * 64, 64, 64));
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
