#include "Global.h"

float ratio(const float ratio_double) { return (float)pow(0.5, 1. / ratio_double); }
const float difficulty_ratio = ratio(difficulty_double);
const float difficulty_ratio_armor = ratio(difficulty_armor);

Player::Player() {

	setSpeed(speed_default);
	setActive(true);
	shape = Player::shape_default;
	setDamage(0.f);
	setHealth(getMaxHealth());

	shots = new Shot[max_shots];
};

float health_up(unsigned n) {
	static float max_factor = Figure::getMaxHealth();
	static float min_factor = Bot::getHealthD();
	return (1.f - (float)pow(difficulty_ratio, n))*(max_factor - min_factor) + min_factor;
};

void Player::setUpShot(float mouse_x, float mouse_y, float rect_x, float rect_y) {

	static int shot_number = 0;

	shots[shot_number++].Shot::setUp(mouse_x, mouse_y, rect_x, rect_y);
	if (shot_number == max_shots) shot_number = 0;
}

void Player::drawShots(sf::RenderWindow &window) {
	for (int i = 0; i < max_shots; i++) {
		shots[i].draw(window);
	}
}

bool Player::collide(Figure &bot) {

	for (int i = 0; i < Player::max_shots; i++)
		if (Figure::collide(shots[i], bot)) {
			kills++;
			money += (int)Bot::getHealthD();
			score += (int)Bot::getHealthD();
			Bot::setPeriodD(Bot::getPeriodD()*difficulty_ratio);
			Bot::setHealthD(health_up(kills));
			Shot::setDamageD(Shot::getDamageD()*difficulty_ratio);
		}

	return Figure::collide(bot, *this);
}

int round2nd(float x) {
	int num = x < 10 ? 1 : (x < 100 ? 10 : (int)pow(10.f, (int)log10(x)-1));
	return num * (int)(x / num); 
}

int Player::increase(Player &player, int price) {
	player.money -= price;
	return round2nd(price*price_increase);
}

int Player::increaseDamage(Player &player, int price) {
	Shot::setDamageD(Shot::getDamageD()/pow(difficulty_ratio,(float)price / Bot::getHealth0()));
	return increase(player,price);
}

int Player::increaseBPS(Player &player, int price) {
	player.setPeriodD(player.getPeriodD()*pow(difficulty_ratio, (float)price / Bot::getHealth0()));
	return increase(player, price);
}

int Player::Regenerate(Player &player, int price) {
	player.setHealth(Player::getMaxHealth());
	return increase(player, price);
}

int Player::increaseArmor(Player &player, int price) {
	Bot::setDamageD(Bot::getDamageD()*difficulty_ratio_armor);
	return increase(player,price);
}

void Player::move_shots() {
	for (int i = 0; i < max_shots; i++) {
		shots[i].move();
	}
}