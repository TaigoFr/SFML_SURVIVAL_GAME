#pragma once

//temporary
#include <iostream>

#include "Figure.h"
#include "MyShape.h"

#include <time.h>

class Bot :public Figure
{
public:
	Bot();

	void setUp();

	sf::Vector2f getSize() { return shape.getSize(); }

	static void setHealthD(float h) { health_default = h; }
	static float getHealthD() { return health_default; }

	static void setPeriodD(float p) { period_default = p; }
	static float getPeriodD() { return period_default; }

	static void setDamageD(float d) { damage_default = d; }
	static float getDamageD() { return damage_default; }

	static float getHealth0() { return health_0; }
	static float getDamage0() { return damage_0; }
	static float getPeriod0() { return period_0; }

	void move(float rect_x, float rect_y);

private:
	float frame_count;

	static const float health_0;
	static const float damage_0;
	static const float period_0;

	static float health_default;
	static float damage_default;
	static float period_default;
	static const float speed_default;

	static const float dumbness;

	static const MyShape shape_default;
};

