#pragma once
#include "Libs.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;
class SliderBar : public Clicable {
	Texture* texture;
	Image* image;
	Sprite* sprite;
	int def_per;
	Color color;
public:
	SliderBar(int sx, int sy, int px, int py, RenderTarget* tg, int percent, Color cl, Mouse* mouse);

	void update();
	void setActive() override;
	void isActive() override;
	void draw() override;
	~SliderBar();
};