#include "ColorSel.h"
#include "Singleton.h"
#include "wingdi.h"

ColorSel::ColorSel(int pos_x, int pos_y, int size_x, int size_y)
{
	rect = std::make_unique<sf::RectangleShape>();
	text = std::make_unique<sf::Text>();
	
	text->setString("This1is1color1which1you1choose");
	text->setFillColor(sf::Color::Black);


	rect->setFillColor(*Singleton::instance().getMainColor());
	text->setFont(*Singleton::instance().getGlobalFont()); // pt = 4/3 px px = 3/4pt
	rect->setSize(sf::Vector2f(0.7 * size_x, 0.5 * size_y));
	text->setCharacterSize(36);
	//(rect->getSize().x / 0.7528f) / (text->getString().getSize())
	text->setPosition((pos_x - text->getLocalBounds().width) / 2.f, 0.15 * size_y);
	rect->setPosition((pos_x - rect->getSize().x) / 2.f, pos_y + 0.6 * size_y);
	ObjTar = Singleton::instance().getPoolWindow()[0].get();
	std::cout << "||||||| RECT size " << rect->getSize().x << "||||||||||| characters SIze "
		<< text->getCharacterSize() << '\n';
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
