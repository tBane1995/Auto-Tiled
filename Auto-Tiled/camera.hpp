#ifndef camera_hpp
#define camera_hpp

class Camera {
public:
	sf::Vector2f position;
	sf::View view;

	Camera() {
		position = sf::Vector2f(0, 0);
		view.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
		view.setCenter(position);
	}

	~Camera();

	void setPosition(float x, float y) {

		this->position.x = x;
		this->position.y = y;
	}

	void setPosition(sf::Vector2f position) {

		this->position = position;
	}

	void move(float x, float y) {

		this->position.x += x;
		this->position.y += y;
	}

	void update() {

		view.setCenter(position);
	}
};

Camera* cam = nullptr;

#endif