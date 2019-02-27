#pragma once

#include <string.h>

#include "Figure.h"
#include "MyShape.h"

class Shot: public Figure
{
public:
	Shot();
	Shot(float mouse_x, float mouse_y, float xx, float yy) : Shot() { setUp(mouse_x, mouse_y, xx, yy); };

	void move();

	void draw(sf::RenderWindow &window);

	void setUp(float mouse_x, float mouse_y, float xx, float yy);
	
	sf::Vector2f getSize() { return shape.getSize(); }

	static float getDamage0() { return damage_0; }
	static float getHealth0() { return health_0; }


	static void setDamageD(float d) { damage_default = d; }
	static float getDamageD() { return damage_default; }

	static void setHealthD(float h) { health_default = h; }
	static float getHealthD() { return health_default; }

private:

	static const float damage_0;
	static const float health_0;

	static float damage_default;
	static float health_default;
	static const float speed_default;

	static const MyShape shape_default;
};