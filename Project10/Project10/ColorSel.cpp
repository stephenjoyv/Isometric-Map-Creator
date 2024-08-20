#include "ColorSel.h"

ColorSel::ColorSel(int pos_x, int pos_y, int size_x, int size_y)
{
	rect = std::make_unique<sf::RectangleShape>();
	text = std::make_unique<sf::Text>();
	
	text->setString("This is color which you choose");
	rect->setFillColor(*Singleton::instance().getMainColor());
	text->setFont(*Singleton::instance().getGlobalFont());
	text->setPosition((pos_x - text->getLocalBounds().width) / 2.f,0.15*size_y);
	rect->setSize(sf::Vector2f(0.7 * size_x, 0.5 * size_y));
	rect->setPosition((pos_x - rect->getSize().x) / 2.f, pos_y + 0.6 * size_y);
	ObjTar = Singleton::instance().getPoolWindow()[0].get();
}

void ColorSel::changeColor(const sf::Color& color)
{
	rect->setFillColor(color);
}

sf::Color ColorSel::getColor()
{
	return rect->getFillColor();
}

void ColorSel::draw()
{
	ObjTar->draw(*text);
	ObjTar->draw(*rect);

}
