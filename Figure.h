#pragma once

#include <SFML/Graphics.hpp>

#include "MyShape.h"

class Figure{
public:
	Figure(float xx = 0, float yy = 0, float vxx = 0, float vyy = 0, float sspeed = 0);

	virtual void move(float vxx, float vyy) { setVel(vxx, vyy); move(); }
	virtual void move();

	void setUp(float xx, float yy);
	void setVel(float vxx, float vyy);

	void setSpeed(float sspeed) { speed = sspeed; }

	float getX() { return x; }
	float getY() { return y; }
	float getVX() { return vx; }
	float getVY() { return vy; }
	
	bool collide(Figure &fig) { return collide(*this, fig); }
	static bool collide(Figure &fig1, Figure &fig2);

	virtual void draw(sf::RenderWindow &window) { if (active) shape.draw(window); }

	virtual sf::Vector2f getSize()=0;

	static float getMaxHealth() { return max_health; }

	void setHealth(float h, bool color=true) { health = h; if(color && h>=0) setColor(); }
	float getHealth() { return health; }

	void setDamage(float h) { damage = h; }
	float getDamage() { return damage; }

	void setActive(bool b) { active = b; }
	bool getActive() { return active; }

protected:
	MyShape shape;
	void setColor();

private:
	bool active = false;
	float damage, health;

	static const float max_health;

	float x, y;
	float vx, vy;
	float speed;

	static float reduce;
	float speedY();
};

float rainbow(float x);
sf::Color color(float x);
sf::Color color_2(float x, float compress = 0.1f);