#include "Global.h"

float rainbow(float x) {return fminf(fmaxf(-6 * fabs(x) + 1.5f, 0), 1);}
sf::Color color(float x) {return sf::Color((sf::Uint8)(rainbow(x - 0.75f) * 255), (sf::Uint8)(rainbow(x - 0.5f) * 255), (sf::Uint8)(rainbow(x - 0.25f) * 255));}
sf::Color color_2(float x, float compress) { return color((1.f - sqrt(x))*(1.f - compress) + compress); }
void Figure::setColor() {shape.setFillColor(color_2(health / Figure::max_health));}

Figure::Figure(float xx, float yy, float vxx, float vyy, float sspeed) {
	setUp(xx, yy);
	setVel(vxx,vyy);
	setSpeed(sspeed);
};

void Figure::move() {
	if (!active) return;
	x += vx * speedY();
	y += vy * speedY();
	shape.setPosition(x, y);
	shape.setSize(y);
}

void Figure::setUp(float xx, float yy) {
	x = xx;
	y = yy;
	shape.setPosition(x,y);
	shape.setSize(y);
}

void Figure::setVel(float vxx, float vyy) {
	vx = vxx;
	vy = vyy;
}


float Figure::reduce = 7.;
float Figure::speedY() { return (float)(speed*delay * (((reduce - 1.) / reduce) * (y - screenHeight) / (screenHeight - boundary_y) + 1.)); };

bool Figure::collide(Figure &attacker, Figure &defensor) {
	if (!attacker.active || !defensor.active)
		return false;
	
	if (!((fabs(attacker.getX() - defensor.getX()) <= attacker.getSize().x / 2. + defensor.getSize().x / 2.)
		&& (fabs(attacker.getY() - defensor.getY()) <= attacker.getSize().y / 2. + defensor.getSize().y / 2.)))
		return false;

	attacker.setHealth(attacker.health - defensor.damage);
	defensor.setHealth(defensor.health - attacker.damage);

	if (attacker.health <= 0)
		attacker.active = false;

	if (defensor.health <= 0) {
		defensor.active = false;
		return true;
	}

	return false;
}


