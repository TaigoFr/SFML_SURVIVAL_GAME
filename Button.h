#pragma once
#include <iostream>

#include "MyShape.h"

class Button : public MyShape {
public:
	Button() {};
	Button(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y) { setUp(size_xx, size_yy, colorr, pos_x, pos_y); };

	void setUp(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y);
	
	void draw(sf::RenderWindow &window);

	void setText(std::string ttext, sf::Color color, unsigned char_size, std::string ffont);

	void setSubText(int price,sf::Color color, unsigned char_size, std::string ffont = "");

	void setPosition(float x, float y);

	void setFunction(int(*ffunc)(Player&, int)) { func = ffunc; }

	bool isClicked(float x, float y);
	void Upgrade(Player&);

private:

	static const float up;
	static const float down;

	int(*func)(Player &player, int price) = NULL;

	sf::Font font;
	sf::Text text;
	sf::Text subtext;
	int price;

	void setFont(std::string str) { font.loadFromFile(str); }

	static void setUpText(sf::Text &ttext, std::string str, sf::Color color, unsigned char_size, sf::Font &ffont);

	void setTextPosition();

	void setSubTextPosition();
};

int isClicked(Button *button, int number, sf::Vector2i mouse);