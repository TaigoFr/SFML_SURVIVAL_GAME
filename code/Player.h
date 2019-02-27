#pragma once

#include <iostream>

#include "Figure.h"
#include "MyShape.h"
#include "Shot.h"

class Player : public Figure {
public:
	Player();
	Player(float xx, float yy) : Player() { setUp(xx, yy); };

	~Player() { delete[] shots; }

	sf::Vector2f getSize() { return shape.getSize(); }

	void setPeriodD(float p) { period_default = p; }
	float getPeriodD() { return period_default; }

	float getPeriod0() { return period_0; }
	int getMoney() { return money; }
	int getScore() { return score; }

	void setUpShot(float mouse_x, float mouse_y, float rect_x, float rect_y);

	void drawShots(sf::RenderWindow &window);
	bool collide(Figure &bot);

	static int increaseDamage(Player &player, int price);
	static int increaseBPS(Player &player, int price);
	static int Regenerate(Player &player, int price);
	static int increaseArmor(Player &player, int price);

	void move_shots();

private:

	static int increase(Player &player, int price);

	unsigned kills = 0;
	int money = 0;
	int score = 0;
	float period_default = period_0;

	static const float period_0;
	static const int max_shots;
	static const float speed_default;

	Shot *shots;

	static const MyShape shape_default;
};

int round2nd(float x);
