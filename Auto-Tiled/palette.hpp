#ifndef palette_hpp
#define palette_hpp

class Palette : public ElementGUI {
public:
	sf::Vector2f position;

	Palette() : ElementGUI() {

	}

	~Palette() { }

	
};

Palette* palette = nullptr;

#endif // !map_hpp
