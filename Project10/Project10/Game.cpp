#include "Game.h"
#include "TileMap.h"
#include "interfaceobj.h"
using namespace std;
using namespace sf;

DetectedImage::DetectedImage(string str, Mouse* mouse) {
	ObjTar = pool_window[0].get();
	image = new Image;
	texture = new Texture;
	sprite = new Sprite;
	this->mouse = mouse;
	std::cout << "load is " << image->loadFromFile(str.c_str());
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y * 3 / 4);
}
DetectedImage::DetectedImage() {

}
void DetectedImage::Scale(int xmod, int ymod) {
	Image* tempimage = new Image;
	tempimage->create(160, 160);
	std::cout << tempimage->getSize().x;
	for (int i = 0; i < image->getSize().x; i++)
	{
		int loadedpix = 0;
		for (int j = 0; j < image->getSize().y; j++)
		{
			for (int m = 0; m < ymod; m++)
			{
				tempimage->setPixel(i + (xmod - 1) * i, j + m + (ymod - 1) * j, image->getPixel(i, j));

			}
		}
		for (int j = 0; j < image->getSize().y * ymod; j++)
		{
			for (int t = 0; t < xmod; t++)
			{
				tempimage->setPixel(i + i * (xmod - 1) + t, j, tempimage->getPixel(i + i * (xmod - 1), j));
			}
		}

	}
	delete texture, sprite, image;
	image = tempimage;
	texture = new Texture;
	texture->loadFromImage(*tempimage);
	sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y * 3 / 4);
	sprite->setPosition(texture->getSize().x / 2, texture->getSize().y);

}
void DetectedImage::draw() {
	ObjTar->draw(*sprite);
}
void DetectedImage::setActive() {
	if (Click())
	{
		std::cout << "click\n";
	}
}
bool DetectedImage::Click() {
	RenderWindow* temp = pool_window[0].get();
	update();

	bool in_area = Mouse::isButtonPressed(Mouse::Left) &&
		(mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y < pos_y + size_y) &&
		(mouse->getPosition(*temp).x >= pos_x) &&
		(mouse->getPosition(*temp).x < pos_x + size_x);

	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse->getPosition(*temp).x - pos_x,
			mouse->getPosition(*temp).y - pos_y).a);
		return alpha_pixel;
	}
	return in_area;
}
void DetectedImage::update()
{
	Vector2f temp = sprite->getOrigin();
	pos_x = sprite->getPosition().x - temp.x;
	pos_y = sprite->getPosition().y - temp.y;
	size_x = texture->getSize().x;
	size_y = texture->getSize().y;
}


void game(RenderTarget* window) {
	Mouse mouse;
	/*Tile m("tyles/tile_022.png", &mouse);
	Tile k = m;*/
	Map fir(string("daw"), &mouse);
	//b.sprite->setPosition(a.sprite->getPosition().x, a.sprite->getPosition().y);
	//Tile* k = new Tile("daw", &mouse);
	
	
	
	
	while (pool_window[0].get()->isOpen())
		{
			Event event;
			while (pool_window[0].get()->pollEvent(event)) {
				switch (event.type)
				{
				case Event::Closed: {
					for (int i = 0; i < pool_window.size(); i++)
					{
						pool_window[i].get()->close();
					}
					break;
				}
				case Event::KeyPressed: {
					switch (event.key.scancode) {
					case Keyboard::W:
					{
						break;
					}
					}
					break;
				}
				case Event::MouseButtonPressed: {

					if (mouse.isButtonPressed(mouse.Left))
					{
					}
					break;
				}
				}

				//Sleep(5);

			}
			for (size_t i = 0; i < pool_button.size(); i++)
			{
				pool_button[i].get()->isActive();
			}
			//std::cout << '\n';
			//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';
			pool_window[0].get()->clear();

			globalDraw();
			fir.draw();
			pool_window[0].get()->display();
		}
}