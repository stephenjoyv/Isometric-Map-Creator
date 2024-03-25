#include "Game.h"
#include "TileMap.h"
#include "TilePanel.h"
#include "interfaceobj.h"
#include "Platform.h"
using namespace std;
using namespace sf;

DetectedImage::DetectedImage(string str, Mouse* mouse):DetectedImage() {
	link = str;
	ObjTar = pool_window[0].get();
	image = new Image;
	texture = new Texture;
	sprite = new Sprite;
	this->mouse = mouse;
	image->loadFromFile(link.c_str());
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setOrigin(0, texture->getSize().y * 3 / 4);
	clicked = false;
	update();
}
DetectedImage::DetectedImage() {
	is_bordered = false;
	scale = Vector2i(1, 1);
}
void DetectedImage::setPosition(int x, int y)
{
	sprite->setPosition(x, y);
	update();
	if (is_bordered) borders->setPosition(pos_x, pos_y);
}
void DetectedImage::init_border()
{
	if (!is_bordered)
	{
		is_bordered = true;
		borders = new RectangleShape;
		update();
		borders->setSize(Vector2f(size_x, size_y));
		borders->setPosition(pos_x, pos_y);
		borders->setOutlineColor(Color::White);
		borders->setOutlineThickness(4);
		borders->setFillColor(Color(0, 0, 0, 0));
	}
	
}
Vector2i DetectedImage::getScale()
{
	return scale;
}
Vector2f DetectedImage::getPosition()
{
	return Vector2f(pos_x, pos_y);
}
Vector2f DetectedImage::getSize()
{
	return Vector2f(size_x,size_y);
}
string DetectedImage::getLink()
{
	return link;
}
void DetectedImage::Scale(int xmod, int ymod) {
	scale = Vector2i(scale.x * xmod, scale.y * ymod);
	Image* tempimage = new Image;
	tempimage->create(size_x*xmod, size_y*xmod);
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
	update();

}
void DetectedImage::draw() {
	ObjTar->draw(*sprite);
	if (is_bordered) ObjTar->draw(*borders);
}
void DetectedImage::setActive() {
	if (Click())
	{
		//Mark on image pixel which was clicked
		/*update();
		int mpx = mouse->getPosition(*pool_window[0].get()).x, mpy = mouse->getPosition(*pool_window[0].get()).y;
		image->setPixel(mpx - pos_x, mpy - pos_y, Color::Red);
		texture->loadFromImage(*image);
		sprite->setTexture(*texture);*/
		std::cout << "click\n";
	}
}
bool DetectedImage::Click() {
	RenderWindow* temp = pool_window[0].get();
	update();
	//std::cout <<"mouse position "<< mouse->getPosition().x << " " << mouse->getPosition().y << '\n';
	bool in_area = Mouse::isButtonPressed(Mouse::Left) &&
		(mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y < pos_y + size_y) &&
		(mouse->getPosition(*temp).x >= pos_x) &&
		(mouse->getPosition(*temp).x < pos_x + size_x);
	if (is_bordered) {
		clicked = true;
		return in_area;
	}
	if (in_area)
	{
		bool alpha_pixel = (bool)(image->getPixel(mouse->getPosition(*temp).x - pos_x,
			mouse->getPosition(*temp).y - pos_y).a);
		if (alpha_pixel) clicked = true;
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
Map::Map(string symbol_map, Mouse* mouse) {
	ownmap = new Tile * *[40];
	for (int i = 0; i < 40; i++)
	{
		ownmap[i] = new Tile * [40];
	}

	for (int i = 0; i < 40; i++)
	{
		//Tile* tmp = new Tile("tyles/tile_022.png", mouse);
		ownmap[i][0] = new Tile("tyles/tile_022.png", mouse);
		if (i > 0) {
			int preposx = ownmap[i - 1][0]->sprite->getPosition().x, preposy = ownmap[i - 1][0]->sprite->getPosition().y;
			int presizex = ownmap[i - 1][0]->texture->getSize().x / 2;
			int presizey = ownmap[i - 1][0]->texture->getSize().y / 4;
			ownmap[i][0]->sprite->setPosition(preposx + presizex, preposy + presizey);
		}
		else {
			ownmap[i][0]->sprite->setPosition(500, 0);
		}
	}
	for (int i = 0; i < 40; i++)
	{
		for (int j = 1; j < 40; j++)
		{
			ownmap[i][j] = new Tile("tyles/tile_040.png", mouse);
			if (i > 0) {
				int preposx = ownmap[i][j - 1]->sprite->getPosition().x, preposy = ownmap[i][j - 1]->sprite->getPosition().y;
				int presizex = ownmap[i][j - 1]->texture->getSize().x / 2;
				int presizey = ownmap[i][j - 1]->texture->getSize().y * 1 / 4;
				ownmap[i][j]->sprite->setPosition(preposx - presizex, preposy + presizey);
			}
		}
	}

}




void game(RenderTarget* window) {
	Mouse mouse;
	/*Tile m("tyles/tile_022.png", &mouse);
	Tile k = m;*/
	Platform* pl = new Platform(&mouse);
	RectButtonImageRolled* img = new RectButtonImageRolled{ 1400,300,1,"tyles/tile_005.png",[]() {},pool_window[0].get(),&mouse};
	
	
	
	/*SelectedTile *k = new SelectedTile;
	Tile* m = new Tile("tyles/tile_000.png", &mouse);
	m->Scale(5, 5);
	m->setPosition(0, 400);
	k->loadCur(m);*/

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
						//m->setActive();
						pl->leftClicked();
						img->setActive();
						//std::cout << "frames = " << img->getFrames();
					}
					else if (mouse.isButtonPressed(mouse.Right) ){
						pl->rightClicked();
					}
					break;
				}
				}

				//Sleep(5);

			}
			buttonWork();
			//std::cout << '\n';
			//std::cout << "frame " << pool_pair[0].get()->getFrame() << '\n';
			pool_window[0].get()->clear();
			std::cout << "";
			globalDraw();
			pl->draw();
			img->draw();
			
			//m->draw();
			pool_window[0].get()->display();
		}
}