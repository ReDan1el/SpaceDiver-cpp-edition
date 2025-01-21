#include "Obstacle.h"

Obstacle::Obstacle()
{
	texobs.loadFromFile("textures/obstacle1.png");
	Obstcl.setTexture(texobs);
	Obstcl.setOrigin(24, 24);
	restart();
}

Obstacle::~Obstacle(){}

void Obstacle::move(float& time)
{
	newborn = false;
	Obstcl.move(static_cast<float>(-0.5 * time), 0);
	posbonus = Obstcl.getPosition();
	if (Obstcl.getPosition().x < -60) restart();
}

void Obstacle::draw(RenderWindow& window)
{
	window.draw(Obstcl);
}

bool Obstacle::collision(FloatRect object)
{
	if (Obstcl.getGlobalBounds().intersects(object)) return true;
	return false;
}

void Obstacle::restart()
{
	newborn = true;
	float s = static_cast<float>(rand() % 20 + 10);
	float x = static_cast<float>(rand() % 1280 + 1280);
	float y = static_cast<float>(rand() % 540 + 130);

	Obstcl.setPosition(Vector2f(x, y));
	Obstcl.setScale(s/20, s/20);

	posbonus = Obstcl.getPosition();
}

const FloatRect Obstacle::getObstbounds()
{
	return Obstcl.getGlobalBounds();
}