#pragma once
#include "Libs.h"
#include "interfaceobj.h"

class ColorSel : public IBaseClass
{
	std::unique_ptr<sf::RectangleShape> rect;
	std::unique_ptr<sf::Text> text;
	
public:
	ColorSel(int pos_x, int pos_y, int size_x,int size_y);
	void changeColor(const sf::Color&);
	sf::Color getColor();
	void draw() override;
};
