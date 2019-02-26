#include "Global.h"

const float Button::up = 1.f / 3.f;
const float Button::down = 1.f / 4.f;

void Button::setUp(float size_xx, float size_yy, sf::Color colorr, float pos_x, float pos_y) {
	setColor(colorr, size_xx, size_yy);

	MyShape::setPosition(pos_x, pos_y);
};


void Button::draw(sf::RenderWindow &window) {
	MyShape::draw(window);
	if (!text.getString().isEmpty()) window.draw(text);
	if (!subtext.getString().isEmpty()) window.draw(subtext);
}

void Button::setText(std::string ttext, sf::Color color, unsigned char_size, std::string ffont) {

	setFont(ffont);
	setUpText(text, ttext, color, char_size, font);
	setTextPosition();
}

void Button::setSubText(int pprice, sf::Color color, unsigned char_size, std::string ffont) {
	price = pprice;

	bool flag = false;
	if (subtext.getString().isEmpty()) flag = true;

	if (ffont != "") setFont(ffont);
	else if (text.getString().isEmpty()) {
		std::cout << "WARNING: NO FONT DEFINED - NOTHINH DONE" << std::endl;
		return;
	}

	setUpText(subtext, std::to_string(price), color, char_size, font);
	setSubTextPosition();
	if (flag) setTextPosition();
}

void Button::setPosition(float x, float y) {
	MyShape::setPosition(x, y);
	setTextPosition();
	setSubTextPosition();
}


bool Button::isClicked(float x, float y) {

	if ((abs(x - getPosition().x) <= getSize().x / 2) && (abs(y - getPosition().y) <= getSize().y / 2)) {
		return true;
	}
	return false;
}

void Button::Upgrade(Player &player) {
	if (price > player.getMoney()) return;
	if (func != NULL) setSubText(func(player, price), subtext.getFillColor(), subtext.getCharacterSize());

}

void Button::setUpText(sf::Text &ttext, std::string str, sf::Color color, unsigned char_size, sf::Font &ffont) {
	ttext.setFont(ffont);
	ttext.setString(str);
	ttext.setCharacterSize(char_size);
	ttext.setOrigin(ttext.getGlobalBounds().width / 2, ttext.getGlobalBounds().height / 2);
	ttext.setFillColor(color);
}

void Button::setTextPosition() {
	if (text.getString().isEmpty()) return;
	if (subtext.getString().isEmpty())
		text.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	else
		text.setPosition(sf::Vector2f((float)getPosition().x, (float)(getPosition().y - (1. / 2. - up) * getSize().y)));
}

void Button::setSubTextPosition() {
	if (subtext.getString().isEmpty()) return;
	subtext.setPosition(sf::Vector2f((float)getPosition().x, (float)(getPosition().y + (1. / 2. - down) * getSize().y)));
}
	

int isClicked(Button *button, int number, sf::Vector2i mouse) {
	for (int i = 0; i < number; i++)
		if (button[i].isClicked((float)mouse.x, (float)mouse.y))
			return i;

	return -1;
}