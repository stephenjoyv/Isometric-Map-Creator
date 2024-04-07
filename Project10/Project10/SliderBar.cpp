#include "SliderBar.h"
static void makeLine(Image* image, int size, int where, Color color);
SliderBar::SliderBar(int sx, int sy, int px, int py, RenderTarget* tg, int percent,Color cl,Mouse * ms)
{
	size_x = sx;
	size_y = sy;
	pos_x = px;
	pos_y = py;
	ObjTar = tg;
	def_per = percent;
	color = cl;
	mouse = ms;
	image = new Image;
	texture = new Texture;
	sprite = new Sprite;
	image->create(size_x, size_y,Color::Black);
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setPosition(pos_x, pos_y);
}


void SliderBar::update()
{
	pos_x = sprite->getPosition().x;
	pos_y = sprite->getPosition().y;
}

void SliderBar::setActive()
{
	cout << "np-click\n";
	if (Click()) {
		cout << "click\n";
		RenderWindow* temp = pool_window[0].get();
		int x = mouse->getPosition(*temp).x;
		makeLine(image, 5, x - pos_x, color);
		texture->loadFromImage(*image);
	}
}

void SliderBar::isActive()
{
}

void SliderBar::draw()
{
	ObjTar->draw(*sprite);
}

SliderBar::~SliderBar()
{
	if (image != nullptr) delete image;
	if (texture != nullptr) delete texture;
	if (sprite != nullptr) delete sprite;
}

static void makeLine(Image* image,int size, int where,Color color) {
	if (where + size > image->getSize().x) return;

	//зарисованная область до линии
	for (int i = 0; i < where; i++)
	{
		for (int k = 0; k < image->getSize().y; k++)
		{
			image->setPixel(i, k, color);
		}
	}

	//зарисованная линия
	for (int i = where; i < where+size; i++)
	{
		for (int k = 0; k < image->getSize().y; k++)
		{
			image->setPixel(i, k, Color::White);
		}
	}

	//область после линии
	for (int i = where+size; i < image->getSize().x; i++)
	{
		for (int k = 0; k < image->getSize().y; k++)
		{
			image->setPixel(i, k, Color::Black);
		}
	}

	cout << "makelien\n";
}