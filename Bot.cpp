#include "Global.h"


float random(float begin, float end){return ((float)rand()) / RAND_MAX * (end - begin) + begin;}

Bot::Bot(){
	setSpeed(speed_default);
	srand((unsigned)time(NULL));
	shape = Bot::shape_default;
	setDamage(damage_default);
	setHealth(health_default);
};

void Bot::setUp() {
	static float perimeter_y = screenHeight - boundary_y;
	static float perimeter = perimeter_y * 2 + screenWidth;
	float random_loc = random(0, perimeter);

	if (random_loc <= perimeter_y) {
		Figure::setUp(0,screenHeight - random_loc);
	}
	else if (random_loc < perimeter - perimeter_y) {
		Figure::setUp(random_loc - perimeter_y, boundary_y);
	}
	else {
		Figure::setUp(screenWidth,random_loc - screenWidth - perimeter_y + boundary_y);
	}

	setVel(0, 0);
	frame_count = dumbness;

	setActive(true);
	setHealth(health_default);
}

void Bot::move(float rect_x, float rect_y) {
	if (!getActive()) return;

	if (frame_count >= dumbness/delay) {
		float norm = sqrt((rect_x - getX()) *(rect_x - getX()) + (rect_y - getY()) *(rect_y - getY()));
		if (norm == 0)	setVel(0, 0);
		else			setVel((rect_x - getX()) / norm, (rect_y - getY()) / norm);
		frame_count = 0;
	}
	frame_count++;

	Figure::move();

}