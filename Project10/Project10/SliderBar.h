#pragma once
#include "Libs.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;
class SliderBar : public Clicable {
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Image> image;
	std::unique_ptr<sf::Sprite> sprite;
	double color_per;
	Color color_def;
	Color color;
public:
	SliderBar(int sx, int sy, int px, int py, RenderTarget* tg, int percent, Color cl, Mouse* mouse);

	void update();
	void setActive() override;
	bool isActive() override;
	void draw() override;
	double getPercent();
	sf::Color getColor();
	void changeDefColor();
	~SliderBar();
};