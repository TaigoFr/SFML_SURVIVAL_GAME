#include "Global.h"


MyShape::MyShape(sf::Texture &texture, float sx, float sy) {setTexture(texture,sx,sy);};
MyShape::MyShape(std::string file, float sx, float sy) {setFile(file,sx,sy);};
MyShape::MyShape(sf::Color color, float size_x, float size_y) {setColor(color, size_x, size_y);}

MyShape& MyShape::operator=(const MyShape& s) {
	if (s.p_texture != NULL) {
		p_texture = new sf::Texture(*(s.p_texture));
		setTexture(*p_texture, s.getSize().x / s.p_texture->getSize().x, s.getSize().y / s.p_texture->getSize().y);
	}
	else if(s.getTexture()!=NULL){
		setTexture(*s.getTexture(), s.getSize().x / s.getTexture()->getSize().x, s.getSize().y / s.getTexture()->getSize().y);
	}
	else {
		setColor(s.getFillColor(),s.getSize().x,s.getSize().y);
	}

	return *this;
}

void MyShape::setSize(float x, float y) { 
	RectangleShape::setSize(sf::Vector2f(x, y));
	setOrigin(x / 2.f, y / 2.f); 
}
void MyShape::setSize(float y) { setSize(size0.x*scale(y),size0.y*scale(y)); }

void MyShape::setScale(float sx, float sy) {
	size0.x *= sx; size0.y *= sy;
	setSize(size0.x, size0.y);
}

void MyShape::setTexture(const sf::Texture &texture, float sx, float sy) {
	RectangleShape::setTexture(&texture);
	size0.x = (float)texture.getSize().x*sx;
	size0.y = (float)texture.getSize().y*sy;
	setSize(size0.x, size0.y);
}

void MyShape::setFile(std::string file, float sx, float sy) {
	p_texture = new sf::Texture();
	p_texture->loadFromFile(file);
	setTexture(*p_texture, sx, sy);
}

void MyShape::setColor(sf::Color color, float size_x, float size_y) {
	setFillColor(color);
	if ((size_x < 0) || (size_y < 0)) return;
	size0.x = size_x;
	size0.y = size_y;
	setSize(size0.x, size0.y);
}

float MyShape::scale(float yy) { return (float)( (1.f - 1.f/16.f) * (yy - screenHeight) / (screenHeight - boundary_y) + 1.); }