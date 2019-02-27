#include "Global.h"

const MyShape Shot::shape_default = MyShape("bullet.png", sW*0.15f, sH*0.15f);
const MyShape Player::shape_default = MyShape(sf::Color::Blue, sW*80, sH*120);
const MyShape Bot::shape_default = MyShape("warrior.png", sW*0.7f, sH*0.7f);

const int Player::max_shots = 100;

const float Shot::speed_default = sH*1.5f; // px/ms
const float Player::speed_default = sH*0.8f; //px/ms
const float Bot::speed_default = sH*0.2f; //px/ms

const float Figure::max_health = 100.f; //associated with: player - regeneration

const float Bot::dumbness = 300.f; //ms

////////////////////////////////////////////////////////////////////////////////////////

const float Bot::period_0 = 1000.f; //ms - difficulty
const float Player::period_0 = 100.f;//ms - shot - speed

const float Shot::damage_0 = 10.; //shot - damage
const float Bot::damage_0 = 1.0f; //player - armor

const float Shot::health_0 = 1.e-5f; //shot - penetration
const float Bot::health_0 = 20; //difficulty

////////////////////////////////////////////////////////////////////////////////////////

float Bot::period_default = Bot::period_0;

float Shot::damage_default = Shot::damage_0;
float Bot::damage_default = Bot::damage_0;

float Shot::health_default = Shot::health_0;
float Bot::health_default = Bot::health_0;