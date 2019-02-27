#pragma once
#include "Shot.h"
#include "Player.h"
#include "Bot.h"
#include "Button.h"

#include <cmath>

#define PI 3.14159265358979f
#define delay 30.f

// const float screenWidth = sf::VideoMode::getDesktopMode().width*1.f;//800 on old computer
const float screenWidth = sf::VideoMode::getDesktopMode().width*0.5f;//800 on old computer
// const float screenHeight = sf::VideoMode::getDesktopMode().height*.93f;//500 on old computer 
const float screenHeight = sf::VideoMode::getDesktopMode().height*0.5f;//500 on old computer 
const float sW = screenWidth/800.f;
const float sH = screenHeight/500.f; //this one is used to expand speeds and sizes if window is changed unevenly

const float boundary_y = sH*172;
const float boundary_x = sW*30;

const int max_bots = 50;

const float difficulty_double = 200.f; //number of kills necessary for difficulty to double
const float difficulty_armor = 3.f; //number of kills necessary for difficulty to double the armor

const bool print = false;
const bool upgrade = true;

const float price_increase = 1.5f;
