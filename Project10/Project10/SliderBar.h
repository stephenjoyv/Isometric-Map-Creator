#pragma once
#include "Libs.h"
#include "interfaceobj.h"

class SliderBar : public Clicable {
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Image> image;
	std::unique_ptr<sf::Sprite> sprite;
	double color_per;
	sf::Color color_def, color;
public:
	SliderBar(int sx, int sy, int px, int py, sf::RenderTarget* tg, int percent, sf::Color cl, sf::Mouse* mouse);

	void update();
	void setActive() override;
	bool isActive() override;
	void draw() override;
	double getPercent();
	sf::Color getColor();
	void changeDefColor();
};