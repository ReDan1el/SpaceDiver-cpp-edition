#include "Full.h"

Full::Full(String name, int x, int y)
{
	texobs.loadFromFile(name);
	Obstcl.setTexture(texobs);
	restart();
}

Full::~Full(){}

void Full::restart()
{
	newborn = true;
	float x = static_cast<float>(rand() % 1280 + 1280);
	float y = static_cast<float>(rand() % 540 + 130);

	Obstcl.setPosition(Vector2f(x, y));

	posbonus = Obstcl.getPosition();
}
