#include "SliderBar.h"
double makeLine(Image* image, int size, int where, Color color);
SliderBar::SliderBar(int sx, int sy, int px, int py, RenderTarget* tg, int percent,Color cl,Mouse * ms)
{
	size_x = sx;
	size_y = sy;
	pos_x = px;
	pos_y = py;
	ObjTar = tg;
	color = cl;
	mouse = ms;
	image = std::make_unique<sf::Image>();
	texture = std::make_unique<sf::Texture>();
	sprite = std::make_unique<sf::Sprite>();
	image->create(size_x, size_y,Color::Black);
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setPosition(pos_x, pos_y);
	changeDefColor();
}


void SliderBar::update()
{
	pos_x = sprite->getPosition().x;
	pos_y = sprite->getPosition().y;
}

void SliderBar::setActive()
{
	//cout << "np-click\n";
	if (Click()) {
		//cout << "click\n";
		RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();
		int x = mouse->getPosition(*temp).x;
		color_per = makeLine(image.get(), 5, x - pos_x, color);
		texture->loadFromImage(*image);
	}
}

bool SliderBar::isActive()
{
	return false;
}

void SliderBar::draw()
{
	ObjTar->draw(*sprite);
}

double SliderBar::getPercent()
{
	return color_per;
}

sf::Color SliderBar::getColor()
{
	return color_def;
}

void SliderBar::changeDefColor()
{
	color_def = *Singleton::instance().getBackgroundColor();
}

//template <typename T>
//static void delSm(T* obj);

double makeLine(Image* image,int size, int where,Color color) {
	if (where + size > image->getSize().x) return 0;

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
	std::cout << "slider size " << image->getSize().x << '\n';
	std::cout << "line pos " << where << '\n';
	return where*1.f/image->getSize().x;
	
}
//
//template <typename T>
//static void delSm(T* obj) {
//	if (obj != nullptr) delete obj;
//}