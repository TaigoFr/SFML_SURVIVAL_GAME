#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

class MyShape : public sf::RectangleShape {
public:
	MyShape() { size0 = sf::Vector2f(0,0); };
	MyShape(sf::Texture &texture, float sx = 1., float sy = 1.);
	MyShape(std::string file, float sx = 1., float sy = 1.);
	MyShape(sf::Color color, float size_x, float size_y);

	~MyShape() { if (p_texture != NULL) delete p_texture; }

	MyShape& operator=(const MyShape& s);

	void setSize(float x, float y);
	void setSize(float y);

	void setScale(float sx, float sy);
	void setTexture(const sf::Texture &texture, float sx = 1., float sy = 1.);
	void setFile(std::string file, float sx = 1., float sy = 1.);
	void setColor(sf::Color color, float size_x = -1.f, float size_y = -1.f);

	virtual void draw(sf::RenderWindow &window) { window.draw(*this);}

	static float scale(float yy);

private:
	sf::Vector2f size0;
	sf::Texture *p_texture = NULL;
};