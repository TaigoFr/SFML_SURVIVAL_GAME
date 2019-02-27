#include "Global.h"

Shot::Shot() {
	setSpeed(speed_default);
	setDamage(damage_default);
	shape = Shot::shape_default;
};

void Shot::move() {
	
	Figure::move();
	if (getActive() && ((getX() < 0) || (getX() >= screenWidth) || (getY() < boundary_y - boundary_x / 2) || (getY() >= screenHeight))) setActive(false);

}

void Shot::setUp(float mouse_x, float mouse_y, float xx, float yy) {
	float norm = sqrt((mouse_x - xx) *(mouse_x - xx) +
		(mouse_y - yy) *(mouse_y - yy));

	Figure::setUp(xx, yy);
	if (norm == 0)	setVel(0,1);
	else			setVel((mouse_x - xx) / norm, (mouse_y - yy) / norm);

	setActive(true);
	setHealth(health_default,false); //setHealth not used so that shots don't change color

	return;
}

void Shot::draw(sf::RenderWindow &window) {
	if (getActive()) {
		shape.setRotation(atan2(getVY(), getVX()) * 180.f / PI);
		Figure::draw(window);
	}
}
