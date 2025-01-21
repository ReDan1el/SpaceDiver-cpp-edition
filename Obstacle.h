#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
public:
	Obstacle(); //constructor
	~Obstacle(); //destructor

	void move(float& time);
	void draw(RenderWindow& window);
	bool collision(FloatRect object);
	virtual void restart();
	const FloatRect getObstbounds();
	bool newborn;

	Vector2f getposbonus() {
		return posbonus;
	}

protected:
	Sprite Obstcl;
	Texture texobs;
	Vector2f posbonus;
};

